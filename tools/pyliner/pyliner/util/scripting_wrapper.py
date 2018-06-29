from threading import Event

from pyliner.action import ACTION_RTL, ACTION_TELEM
from pyliner.intent import Intent


# class _AppWrapper(object):
#     def __init__(self, vehicle, mapping):
#         self.vehicle = vehicle
#         self.mapping = mapping
#
#     def __getattr__(self, item):
#         try:
#             return lambda *args, **kwrags: self.mapping[item]()


class ScriptingWrapper(object):
    """Wraps a vehicle for a scripting environment.

    Implements context manager (with-statement) functionality. Unhandled
    exceptions in the context manager are passed to `failure_callback` to
    give the user a chance to fail gracefully before exiting the context
    manager.

    Apps on the vehicle are directly accessible by their qualified name,
    and Apps which are explicitly supported by this wrapper are accessible
    through shorter names.

    Examples:
        with ScriptingWrapper(vehicle) as rocky:
            ... do things
    """
    def __init__(self, vehicle, failure_callback=None):
        """
        Args:
            vehicle (BasePyliner): The vehicle to wrap.
            failure_callback (Callable[[Pyliner, Tuple], None]): Function
                handle that will be invoked on an unhandled exception of the
                controlling script.
        """
        self._vehicle = vehicle
        self.failure_callback = failure_callback
        # self.mapping = {
        #     'nav': _AppWrapper(vehicle, {
        #         ''
        #     })
        # }

    def __getattr__(self, item):
        if hasattr(self._vehicle, item):
            return getattr(self._vehicle, item)

        mapping = {
            'ctrl': 'com.windhover.pyliner.app.controller',
            'fd': 'com.windhover.pyliner.app.flight_director',
            'fence': 'com.windhover.pyliner.app.geofence',
            'geographic': 'com.windhover.pyliner.app.geographic',
            'nav': 'com.windhover.pyliner.app.navigation'
        }

        try:
            return self.app_by_qualified_name(mapping[item])
        except KeyError:
            raise AttributeError('{!r} is not a method or component of this '
                                 'Pyliner instance.'.format(item))

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        # If the context manager exits without error, all good. Otherwise...
        if exc_type:
            if callable(self.failure_callback):
                self.failure_callback(self, (exc_type, exc_val, exc_tb))
            else:
                print('Error in execution. Returning to Launch.')
                self._vehicle.broadcast(Intent(action=ACTION_RTL))

    def app_by_qualified_name(self, qualified_name):
        return self._vehicle.apps[qualified_name].app

    def await_change(self, tlm, poll=1.0, out=None):
        """Block until the telemetry gets a new value.

        The new value does not have to be different than the old value.

        Args:
            tlm (str): The telemetry to monitor.
            poll (float): Check every `poll` seconds.
            out (Callable): If not None, call this every loop.
        """

        telemetry = self.broadcast(Intent(
            action=ACTION_TELEM,
            data=tlm
        )).first().result
        change = Event()
        telemetry.add_listener(lambda t: change.set())
        change.wait(poll)
        while not change.is_set():
            if callable(out):
                out()
            change.wait(poll)
