class VehicleAccess(object):
    def __init__(self, vehicle, name, to):
        self._to = to
        self._name = name
        self._vehicle = vehicle
        self._filter = set()

    def add_filter(self, predicate, callback):
        if not callable(predicate) or not callable(callback):
            raise ValueError('Filter predicate and callback must be callable.')
        else:
            self._filter.add((predicate, callback))
        return predicate, callback

    def clear_filter(self):
        self._filter.clear()

    def event(self, event):
        for predicate, callback in self._filter:
            if predicate(event):
                callback(event)

    def remove_filter(self, predicate_callback):
        self._filter.remove(predicate_callback)
