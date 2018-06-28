from pyliner.action import ACTION_RTL
from pyliner.intent import Intent


class ScriptingWrapper(object):
    def __init__(self, vehicle, failure_callback=None):
        """Wraps a vehicle for a scripting environment.

        Implements context manager (with-statement) functionality. Unhandled
        exceptions in the context manager are passed to `failure_callback` to
        give the user a chance to fail gracefully before exiting the context
        manager.

        Apps on the vehicle are directly accessible by their qualified name,
        and Apps which are explicitly supported by this wrapper are accessible
        through .

        Args:
            vehicle (BasePyliner): The vehicle to wrap.
            failure_callback (Callable[[Pyliner, Tuple], None]): Function
                handle that will be invoked on an unhandled exception of the
                controlling script.
        """
        self._vehicle = vehicle
        self.failure_callback = failure_callback

    def app_by_qualified_name(self, qualified_name):
        return self._vehicle._apps[qualified_name]

    def __getattr__(self, item):
        if hasattr(self._vehicle, item):
            return getattr(self._vehicle, item)

        app_names = ((k.split('.')[-1], v) for k, v in self._vehicle._apps.items())
        filter_names = list(filter(lambda a: a[0].startswith(item), app_names))
        if len(filter_names) == 1:
            return filter_names[0][1]._app
        elif len(filter_names) > 1:
            raise AttributeError(
                '{!r} cannot be resolved to a unique App. Matched {}'.format(
                    item, (a[0] for a in filter_names)))
        else:
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
