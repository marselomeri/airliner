"""
The Vehicle Access module provides a token-ish interface for a component to
interact with a vehicle, and the other components of the vehicle.

Classes:
    VehicleAccess  Access controller between a Vehicle and its components.
"""
from pyliner.intent import IntentResponse
from pyliner.util.loggable import Loggable


class VehicleAccess(Loggable):
    """
    The VehicleAccess class acts as a boundary between components on a vehicle
    so that they do not interact destructively with each other. Components must
    access the vehicle through the interface provided by their VehicleAccess.
    """
    def __init__(self, name):
        super(VehicleAccess, self).__init__()
        self.callback = None
        self._component = None
        self._name = name
        self._vehicle = None
        self._filter = set()

    # Events
    def add_filter(self, predicate, callback):
        """Add an intent filter to this access and return a tuple.

        When an intent is broadcast which passes the predicate, the callback is
        invoked. Repeated calls with the same arguments will still result in a
        single call to `callback`.

        Returns:
            Tuple of (predicate, callback) which must be passed into
                remove_filter to remove the filter.
        """
        if not callable(predicate) or not callable(callback):
            raise ValueError('Filter predicate and callback must be callable.')
        else:
            self._filter.add((predicate, callback))
        return predicate, callback

    def clear_filter(self):
        """Remove all event filters."""
        self._filter.clear()

    def receive(self, intent, response=None):
        """Receive an intent and pass it to any callbacks that are listening."""
        if callable(self.callback):
            self.callback(intent)
        for predicate, callback in self._filter:
            if predicate(intent):
                resp = callback(intent)
                if response and resp:
                    response.add(resp)

    def broadcast(self, intent):
        """Broadcast an intent to the vehicle."""
        return self._vehicle.broadcast(intent)

    def remove_filter(self, predicate_callback):
        """Remove a filter (by the tuple returned by add) from this access."""
        self._filter.remove(predicate_callback)
