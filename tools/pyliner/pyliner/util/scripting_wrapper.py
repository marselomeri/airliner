from pyliner.action import ACTION_RTL
from pyliner.intent import Intent


class ScriptingWrapper(object):
    def __init__(self, vehicle, failure_callback=None):
        """Wraps a vehicle for a scripting environment.

        Implements context manager (with-statement) functionality. Unhandled
        exceptions in the context manager are passed to `failure_callback` to
        give the user a chance to fail gracefully before exiting the context
        manager.

        Apps on the vehicle are accessible by their name (pyliner.app).

        Args:
            vehicle (BasePyliner): The vehicle to wrap.
            failure_callback (Callable[[Pyliner, Tuple], None]): Function
                handle that will be invoked on an unhandled exception of the
                controlling script.
        """
        self._vehicle = vehicle
        self.failure_callback = failure_callback

    def __getattr__(self, item):
        if hasattr(self._vehicle, item):
            return getattr(self._vehicle, item)
        apps = self._vehicle.components['app']
        services = self._vehicle.components['service']
        sensors = self._vehicle.components['sensor']
        if item in apps:
            return apps[item]._component
        if item in services:
            return services[item]._component
        if item in sensors:
            return sensors[item]._component
        raise AttributeError('{} is not a method or component of this '
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
