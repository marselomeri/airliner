from util import Loggable


class VehicleAccess(Loggable):
    def __init__(self, name):
        super(VehicleAccess, self).__init__()
        self._component = None
        self._name = name
        self._vehicle = None
        self._filter = set()

    # Vehicle Access
    # TODO wrap access in case of Access Denial
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
