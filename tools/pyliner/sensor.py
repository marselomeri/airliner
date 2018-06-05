from enum import Enum

from pyliner_exceptions import InvalidStateError
from vehicle_access import VehicleAccess


class SensorState(Enum):
    ATTACHED = 'ATTACHED'
    DETACHED = 'DETACHED'


class Sensor(object):
    """A Sensor is a long-running passive component of Pyliner.
    
    A sensor is given a VehicleAccess token when it is attached but other
    components of Pyliner may access public members of the instance directly.
    Use sensors to collect telemetry and synthesize it into useful public
    attributes of the sensor.

    Sensors are responsive. They register for telemetry events and receive
    requests from other components but should not be actively running side
    tasks. Use a Service for components that generate events.

    Lifecycle:
        attach -> detach
    """

    def __init__(self):
        self._state = SensorState.DETACHED
        self.vehicle = None
        """:type: VehicleAccess"""

    def attach(self, vehicle_wrapper):
        # type: (VehicleAccess) -> None
        """Called when the sensor is attached to a vehicle.

        The service is given a wrapper to interact with the vehicle it has been
        attached to. Use this wrapper for platform-dependant operations.
        """
        if self._state is not SensorState.DETACHED:
            raise InvalidStateError('Service must be detached before attaching.')
        self._state = SensorState.ATTACHED
        self.vehicle = vehicle_wrapper

    def detach(self):
        """Called when the sensor is detached from a vehicle.

        The wrapper will be valid until this method returns, after which the
        vehicle will no longer respond to calls through the wrapper nor pass
        events through to the service.

        Sets vehicle to None.
        """
        if self._state is not SensorState.ATTACHED:
            raise InvalidStateError('Service must be stopped before detaching.')
        self._state = SensorState.DETACHED
        self.vehicle = None

    @property
    def state(self):
        """The state of the sensor."""
        return self._state
