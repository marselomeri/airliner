class VehicleAccess(object):
    # TODO When service or app is detached do something

    def __init__(self, vehicle, name, to):
        self._to = to
        self._name = name
        self._vehicle = vehicle
        self._filter = set()
        self._logger = vehicle.logger.getChild(name)

    def add_filter(self, predicate, callback):
        if not callable(predicate) or not callable(callback):
            raise ValueError('Filter predicate and callback must be callable.')
        else:
            self._filter.add((predicate, callback))
        return predicate, callback

    def app(self, name):
        return self._vehicle.apps[name]

    def clear_filter(self):
        self._filter.clear()

    def critical(self, msg):
        self._logger.critical(msg)

    def debug(self, msg, *args, **kwargs):
        self._logger.debug(msg, *args, **kwargs)

    def error(self, msg, *args, **kwargs):
        self._logger.error(msg, *args, **kwargs)

    def exception(self, msg, *args, **kwargs):
        self._logger.exception(msg, *args, **kwargs)

    @property
    def logger(self):
        return self._logger

    def post_event(self, event):
        for predicate, callback in self._filter:
            if predicate(event):
                callback(event)

    def push_event(self, event):
        self._vehicle.event(event)

    def info(self, msg, *args, **kwargs):
        self._logger.info(msg, *args, **kwargs)

    def remove_filter(self, predicate_callback):
        self._filter.remove(predicate_callback)

    def sensor(self, name):
        return self._vehicle.sensors[name]

    def service(self, name):
        return self._vehicle.services[name]

    def start(self):
        self._to.start()

    def stop(self):
        self._to.stop()

    def warning(self, msg, *args, **kwargs):
        self._logger.warning(msg, *args, **kwargs)
