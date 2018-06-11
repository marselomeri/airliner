from collections import Iterable

from service import Service, ServiceAccess


class App(Service):
    """Apps respond to events and control the vehicle when appropriate.

    An app that is attached to a vehicle may be enabled or disabled at any time.
    If an app requests control of the vehicle it must wait until such control is
    granted before and commands that it sends are accepted.
    """
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
        return lambda self: self.vehicle._vehicle.tlm_value(name)


class AppAccess(ServiceAccess):
    pass
