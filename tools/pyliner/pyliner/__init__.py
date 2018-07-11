"""
The Vehicle module provides the user with a concrete implementation of
BaseVehicle, with some useful modules and settings pre-loaded. The user is free
to not use Vehicle in favor of a completely custom subclass of BaseVehicle.

Classes:
    Vehicle  A vehicle for the user to control.
"""
from abc import abstractmethod
from threading import Event

from pyliner import AppDetachedError, IntentFilter, Intent
from pyliner.action import ACTION_CONTROL_GRANT, ACTION_CONTROL_REVOKE, \
    ACTION_CONTROL_REQUEST, ACTION_CONTROL_RELEASE
from pyliner.app_access import InvalidStateError, AppDetachedError
from pyliner.apps.controller import Controller
from pyliner.apps.flight_director import FlightDirector
from pyliner.apps.geofence import Geofence, LayerKind
from pyliner.apps.geographic_app import GeographicApp
from pyliner.apps.navigation import Navigation
from pyliner.apps.time_app import TimeApp
from pyliner.base_vehicle import BaseVehicle
from pyliner.intent import IntentFilter, Intent
from pyliner.util.loggable import Loggable

__version__ = '0.3'


class Vehicle(BaseVehicle):
    """Represents a vehicle that the user may control.

    The basic apps that a vehicle presents are:
        com (Communication): Provides methods to communicate with the physical
            vehicle in the air.
        fd (FlightDirector): Provides methods for controlling the raw x, y, z,
            and rotation axes of the vehicle.
        nav (Navigation): Provides methods for controlling the direction and
            speed of the vehicle.

    The user is free to replace the defaults of these apps in the constructor
    but it is highly recommended that replacements subclass the default apps.
    """

    def __init__(self, vehicle_id, communication, geographic=None, time=None,
                 logger=None):
        """Create an instance of Pyliner.

        Args:
            vehicle_id: Vehicle ID. Should be unique.
            communication (Communication): Communication App.
                Not exposed as a public module for direct access, but the user
                is given the option to use a custom class if they desire.
            geographic: If None, defaults to Geographic().
            logger: If None, defaults to 'logging.getLogger(vehicle_id)'.
            time: If None, default to TimeSensor().
        """
        super(Vehicle, self).__init__(vehicle_id, logger)

        # Attributes
        self.atp_override = None

        # Component Defaults
        communication = communication
        controller = Controller()
        flight_director = FlightDirector()
        geofence = Geofence()
        geographic = geographic or GeographicApp()
        navigation = Navigation()
        time = time or TimeApp()

        # Attach defaults
        self.attach_app(communication)
        self.attach_app(geographic)
        # self.attach_service(time)
        self.attach_app(geofence)
        self.attach_app(controller)
        self.attach_app(flight_director)
        self.attach_app(navigation)

        # Add helpful default settings
        geofence.add_layer(0, 'base', LayerKind.ADDITIVE)
        navigation.defaults.update({'timeout': None, 'underflow': 5.0})


class App(Loggable):
    """Apps respond to events and control the vehicle when appropriate.
    A Sensor is a long-running passive component of Pyliner.

    An app may be attached or detached at any time by the program. In the event
    that an app is detached, it should cease any auxiliary tasks by stopping
    threads or disabling event listeners.

    A app is given an AppAccess token when it is attached. This token is how
    the app broadcasts and receive intents from the vehicle it is attached to.

    Apps should be responsive. They can register for telemetry events and
    receive intents from other apps.

    If an app requests control of the vehicle it must wait until such control is
    granted before and commands that it sends are accepted.

    Lifecycle:
           +--------------------------+
           v                          |
        attach -> start <-> stop -> detach
    """

    ATTACHED = 'ATTACHED'
    DETACHED = 'DETACHED'

    def __init__(self):
        super(App, self).__init__()
        self._state = App.DETACHED
        self.vehicle = None
        """:type: AppAccess"""

    @property
    @abstractmethod
    def qualified_name(self):
        # type: () -> str
        """The system-unique identifier for this App.

        This name is used for explicit intent resolution.
        """
        raise NotImplementedError()

    @property
    def state(self):
        """The state of the App, ATTACHED or DETACHED."""
        return self._state

    def attach(self, vehicle_wrapper):
        # type: (AppAccess) -> None
        """Called when the app is attached to a vehicle.

        Call super before any subclass code.

        The app is given a wrapper to interact with the vehicle it has been
        attached to. Use this wrapper for platform-dependant operations.

        The app should start any threads or processes that it runs here.
        """
        if self._state is App.ATTACHED:
            raise InvalidStateError('Service is currently attached.')
        self._state = App.ATTACHED
        self.vehicle = vehicle_wrapper
        self.logger = vehicle_wrapper.logger

    def detach(self):
        """Called when the app is detached from a vehicle.

        Call super after any subclass code if the user code depends on vehicle
        or any logging calls.

        The wrapper will be valid until this method returns, after which the
        vehicle will no longer respond to calls through the wrapper nor pass
        events through to the app.

        The service should stop any threads or processes that it started.
        """
        if self._state is App.DETACHED:
            raise AppDetachedError('Service cannot be detached at this time.')
        self._state = App.DETACHED
        self.vehicle = None
        self.logger = None

    def control_block(self):
        if self.state is App.DETACHED:
            raise AppDetachedError('Detached App will never get control.')
        return _ControlBlock(self)


class _ControlBlock(object):
    def __init__(self, app):
        self.app = app

        self._auth = None
        """:type: ControlToken"""
        self._control = Event()
        self._exit = False
        self._grant_filter = None
        self._revoke_filter = None

    def __enter__(self):
        self._grant_filter = self.app.vehicle.add_filter(
            intent_filter=IntentFilter(actions=[ACTION_CONTROL_GRANT]),
            callback=lambda i: self.grant(i.data)
        )
        self._revoke_filter = self.app.vehicle.add_filter(
            intent_filter=IntentFilter(actions=[ACTION_CONTROL_REVOKE]),
            callback=lambda i: self.revoke()
        )

        self.app.vehicle.broadcast(Intent(
            action=ACTION_CONTROL_REQUEST,
            data=self.app.qualified_name
        ))
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self._control.wait()
        self.app.vehicle.broadcast(Intent(
            action=ACTION_CONTROL_RELEASE,
            data=self._auth
        ))
        self.app.vehicle.remove_filter(self._grant_filter)
        self.app.vehicle.remove_filter(self._revoke_filter)

    def broadcast(self, intent):
        self._control.wait()
        return self.app.vehicle.broadcast(intent)

    def grant(self, data):
        if self._exit:
            return False
        else:
            self._auth = data
            self._control.set()
            return True

    def request(self, data):
        self._control.wait()
        return self._auth.request(data)

    def revoke(self):
        self._auth = None
        self._control.clear()