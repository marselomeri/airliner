from collections import Iterable

from enum import Enum
from typing import Optional

from vehicle_access import VehicleAccess


class AppState(Enum):
    DETACHED = 'DETACHED'
    STARTED = 'STARTED'
    STOPPED = 'STOPPED'


class App(object):
    """Apps respond to events and control the vehicle when appropriate.

    An app that is attached to a vehicle may be enabled or disabled at any time.
    If an app requests control of the vehicle it must wait until such control is
    granted before and commands that it sends are accepted.
    """
    def __init__(self):
        self.vehicle = None

    def attach(self, vehicle):
        # type: (VehicleAccess) -> None
        """Attach this app to a vehicle.

        Use this vehicle for platform-dependant operations.
        """
        if self.vehicle is not None:
            raise ValueError('Cannot reattach an app while it is currently'
                             'attached. Detach first.')
        self.vehicle = vehicle

    def detach(self):
        """Detach the previously attached vehicle from this module.

        The module will not perform any operations on the vehicle anymore.
        """
        self.vehicle = None

    @classmethod
    def required_telemetry_paths(cls):
        # type: () -> Optional[Iterable[str]]
        """Return the required telemetry to enable this module.

        Return:
            Iterable[str]: An iterable of telemetry paths required.
                May be None if no telemetry is required.
        """
        return None

    @property
    def telemetry(self):
        return None

    @property
    def telemetry_available(self):
        return False

    @staticmethod
    def _telem(name):
        return lambda self: self.vehicle.tlm_value(name)
