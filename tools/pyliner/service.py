from enum import Enum

from pyliner_exceptions import InvalidStateError


class ServiceState(Enum):
    DETACHED = 'DETACHED'
    STARTED = 'STARTED'
    STOPPED = 'STOPPED'


class Service(object):
    """Services are long-running passive components to Pyliner.

    A service may be started or stopped at any time by the program. Services
    are not granted control access to the vehicle.

    Service Lifecycle:
        attach -> start -> stop -> detach
    """

    def __init__(self):
        self._state = ServiceState.DETACHED
        self.vehicle = None
        """:type: ServiceWrapper"""

    def attach(self, service_wrapper):
        """Called when a service is attached to a vehicle.

        The service is given a wrapper to interact with the vehicle it has been
        attached to.
        """
        if self._state is not ServiceState.DETACHED:
            raise InvalidStateError('Service must be detached before attaching.')
        self._state = ServiceState.STOPPED
        self.vehicle = service_wrapper

    def detach(self):
        """Called when a service is detached from a vehicle.

        The wrapper will be valid until this method returns, after which the
        vehicle will no longer respond to calls through the wrapper nor pass
        events through to the service.

        Sets vehicle to None.
        """
        if self._state is not ServiceState.STOPPED:
            raise InvalidStateError('Service must be stopped before detaching.')
        self._state = ServiceState.DETACHED
        self.vehicle = None

    def start(self):
        """Called when a service is started.

        The service should start any threads or processes that it runs here.
        """
        if self._state is not ServiceState.STOPPED:
            raise InvalidStateError('Service must be stopped before starting.')
        self._state = ServiceState.STARTED

    def stop(self):
        """Called when a service is stopped.

        The service should stop any threads or processes that it started.
        """
        if self._state is not ServiceState.STARTED:
            raise InvalidStateError('Service must be started before stopping.')
        self._state = ServiceState.STOPPED


class ServiceWrapper(object):
    def __init__(self, vehicle, service_name, service):
        self._service = service
        self._service_name = service_name
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
