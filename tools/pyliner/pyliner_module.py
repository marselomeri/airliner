from abc import abstractmethod
from collections import Iterable


class PylinerModule(object):
    def __init__(self):
        self._vehicle = None
        """:type: BasePyliner"""

    def attach(self, vehicle):
        # type: (BasePyliner) -> None
        """Attach this module to a vehicle.

        Use this vehicle for platform-dependant operations.
        """
        if self._vehicle is not None:
            raise ValueError('Cannot reattach a module while it is currently'
                             'attached. Detach first.')
        self._vehicle = vehicle

    def detach(self):
        """Detach the previously attached vehicle from this module.

        The module will not perform any operations on the vehicle anymore.
        """
        self._vehicle = None

    @classmethod
    @abstractmethod
    def required_telemetry_paths(cls):
        # type: () -> Iterable[str]
        """Return the required telemetry to enable this module.

        Return:
            Iterable[str]: An iterable of telemetry paths required.
                May be None if no telemetry is required.
        """
        raise NotImplementedError()

    @property
    def telemetry(self):
        return None

    @property
    def telemetry_available(self):
        return False

    @staticmethod
    def _telem(name):
        return lambda self: self.vehicle.tlm_value(name)

    @property
    def vehicle(self):
        # type: () -> BasePyliner
        return self._vehicle
