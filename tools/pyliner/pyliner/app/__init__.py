from abc import abstractmethod

from pyliner.pyliner_exceptions import InvalidStateError
from pyliner.util.loggable import Loggable
from pyliner.app_access import AppAccess


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
    # TODO Add App qualified name (com.windhover.pyliner.app.controller, etc)

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

        The app is given a wrapper to interact with the vehicle it has been
        attached to. Use this wrapper for platform-dependant operations.

        The app should start any threads or processes that it runs here.
        """
        if self._state is not App.DETACHED:
            raise InvalidStateError('Service is currently attached.')
        self._state = App.ATTACHED
        self.vehicle = vehicle_wrapper
        self.logger = vehicle_wrapper.logger

    def detach(self):
        """Called when the app is detached from a vehicle.

        The wrapper will be valid until this method returns, after which the
        vehicle will no longer respond to calls through the wrapper nor pass
        events through to the app.

        The service should stop any threads or processes that it started.
        """
        if self._state is not App.ATTACHED:
            raise InvalidStateError('Service cannot be detached at this time.')
        self._state = App.DETACHED
        self.vehicle = None
        self.logger = None
