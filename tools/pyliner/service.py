from enum import Enum

from pyliner_exceptions import InvalidStateError
from vehicle_access import VehicleAccess


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
        self.state = ServiceState.DETACHED
        """State of the Service, DETACHED, STOPPED, or STARTED."""
        self.vehicle = None
        """:type: ServiceWrapper"""

    def attach(self, vehicle_wrapper):
        # type: (VehicleAccess) -> None
        """Called when a service is attached to a vehicle.

        The service is given a wrapper to interact with the vehicle it has been
        attached to.
        """
        if self.state is not ServiceState.DETACHED:
            raise InvalidStateError('Service must be detached before attaching.')
        self.state = ServiceState.STOPPED
        self.vehicle = vehicle_wrapper

    def detach(self):
        """Called when a service is detached from a vehicle.

        The wrapper will be valid until this method returns, after which the
        vehicle will no longer respond to calls through the wrapper nor pass
        events through to the service.

        Sets vehicle to None.
        """
        if self.state is not ServiceState.STOPPED:
            raise InvalidStateError('Service must be stopped before detaching.')
        self.state = ServiceState.DETACHED
        self.vehicle = None

    def start(self):
        """Called when a service is started.

        The service should start any threads or processes that it runs here.
        """
        if self.state is not ServiceState.STOPPED:
            raise InvalidStateError('Service must be stopped before starting.')
        self.state = ServiceState.STARTED

    def stop(self):
        """Called when a service is stopped.

        The service should stop any threads or processes that it started.
        """
        if self.state is not ServiceState.STARTED:
            raise InvalidStateError('Service must be started before stopping.')
        self.state = ServiceState.STOPPED


