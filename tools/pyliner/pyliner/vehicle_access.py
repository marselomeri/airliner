"""
The Vehicle Access module provides a token-ish interface for a component to
interact with a vehicle, and the other components of the vehicle.

Classes:
    VehicleAccess  Access controller between a Vehicle and its components.
"""

from util import Loggable


class VehicleAccess(Loggable):
    """
    The VehicleAccess class acts as a boundary between components on a vehicle
    so that they do not interact destructively with each other. Components must
    access the vehicle through the interface provided by their VehicleAccess.
    """
    def __init__(self, name):
        super(VehicleAccess, self).__init__()
        self._component = None
        self._name = name
        self._vehicle = None
        self._filter = set()

    # Vehicle Access
    # TODO wrap access in case of Access Denial
    def app(self, name):
        """Return the app by name on the vehicle."""
        return self._vehicle.apps[name]

    def sensor(self, name):
        """Return the sensor by name on the vehicle."""
        return self._vehicle.sensors[name]

    def service(self, name):
        """Return the service by name on the vehicle."""
        return self._vehicle.services[name]

    # Events
    def add_filter(self, predicate, callback):
        """Add an event filter to this access and return a tuple.

        When an event which passes the predicate is broadcast, the callback is
        invoked. Both are invoked with the event that was broadcast.
        """
        if not callable(predicate) or not callable(callback):
            raise ValueError('Filter predicate and callback must be callable.')
        else:
            self._filter.add((predicate, callback))
        return predicate, callback

    def clear_filter(self):
        """Remove all event filters."""
        self._filter.clear()

    def handle_event(self, event):
        """Take an event and pass it to any callbacks that are listening."""
        for predicate, callback in self._filter:
            if predicate(event):
                callback(event)

    def push_event(self, event):
        """Broadcast an event to the vehicle."""
        self._vehicle.event(event)

    def remove_filter(self, predicate_callback):
        """Remove a filter (by the tuple returned by add) from this access."""
        self._filter.remove(predicate_callback)
