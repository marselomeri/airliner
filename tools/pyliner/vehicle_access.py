class VehicleAccess(object):
    def __init__(self, name):
        self._component = None
        self._name = name
        self._vehicle = None
        self._filter = set()
        self._logger = None

    # Vehicle Access
    def app(self, name):
        return self._vehicle.apps[name]

    def sensor(self, name):
        return self._vehicle.sensors[name]

    def service(self, name):
        return self._vehicle.services[name]

    # Events
    def add_filter(self, predicate, callback):
        if not callable(predicate) or not callable(callback):
            raise ValueError('Filter predicate and callback must be callable.')
        else:
            self._filter.add((predicate, callback))
        return predicate, callback

    def clear_filter(self):
        self._filter.clear()

    def post_event(self, event):
        for predicate, callback in self._filter:
            if predicate(event):
                callback(event)

    def push_event(self, event):
        self._vehicle.event(event)

    def remove_filter(self, predicate_callback):
        self._filter.remove(predicate_callback)

    # Logging
    def critical(self, msg):
        self._logger.critical(msg)

    def debug(self, msg, *args, **kwargs):
        self._logger.debug(msg, *args, **kwargs)

    def error(self, msg, *args, **kwargs):
        self._logger.error(msg, *args, **kwargs)

    def exception(self, msg, *args, **kwargs):
        self._logger.exception(msg, *args, **kwargs)

    def info(self, msg, *args, **kwargs):
        self._logger.info(msg, *args, **kwargs)

    @property
    def logger(self):
        return self._logger

    def warning(self, msg, *args, **kwargs):
        self._logger.warning(msg, *args, **kwargs)