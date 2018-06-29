"""
The Vehicle Access module provides a token-ish interface for a component to
interact with a vehicle, and the other components of the vehicle.

Classes:
    VehicleAccess  Access controller between a Vehicle and its components.
"""
from pyliner.intent import Intent
from pyliner.intent import IntentFuture, IntentResponse
from pyliner.pyliner_exceptions import InvalidStateError
from pyliner.util.loggable import Loggable


class AppAccess(Loggable):
    """
    The VehicleAccess class acts as a boundary between components on a vehicle
    so that they do not interact destructively with each other. Components must
    access the vehicle through the interface provided by their VehicleAccess.
    """
    def __init__(self, app):
        super(AppAccess, self).__init__()
        self.callback = None
        self.app = app
        self.vehicle = None
        """:type: BaseVehicle"""
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

    def attach(self, vehicle):
        """Attach the App to a Vehicle."""
        self.vehicle = vehicle
        self.logger = vehicle.logger.getChild(self.app.qualified_name)
        self.app.attach(self)

    def clear_filter(self):
        """Remove all event filters."""
        self._filter.clear()

    def detach(self):
        """Detach the App from the Vehicle."""
        self.app.detach()
        self.vehicle = None
        self.logger = None

    def receive(self, intent, future):
        """Receive an intent and pass it to any callbacks that are listening."""
        def handle(cb):
            result = exception = None
            try:
                result = cb(intent)
            except Exception as e:
                exception = e
            if result is not None or exception is not None:
                # self.debug('{} handled at {}: result={} exception={}'.format(
                #     intent, self._name, result, exception))
                future.add(IntentResponse(result=result, exception=exception))

        if callable(self.callback):
            handle(self.callback)
        for predicate, callback in self._filter:
            if predicate(intent):
                handle(callback)

    def broadcast(self, intent):
        # type: (Intent) -> IntentFuture
        """Broadcast an intent to the vehicle."""
        if not self.vehicle:
            raise InvalidStateError('Cannot broadcast while detached.')
        return self.vehicle.broadcast(intent)

    def remove_filter(self, predicate_callback):
        """Remove a filter (by the tuple returned by add) from this access."""
        self._filter.remove(predicate_callback)
