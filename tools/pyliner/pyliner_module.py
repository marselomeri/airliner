from collections import Iterable
from abc import abstractmethod


class PylinerModule(object):
    def __init__(self):
        self._vehicle = None

    def attach(self, vehicle):
        if self._vehicle is not None:
            raise ValueError('Cannot reattach a module while it is currently'
                             'attached. Detach first.')
        self._vehicle = vehicle

    def detach(self):
        self._vehicle = None

    @classmethod
    @abstractmethod
    def required_telemetry_paths(cls):
        """Return the required telemetry to enable this module.

        Return:
            Iterable[str]: An iterable of telemetry paths required.
        """
        raise NotImplementedError()

    @staticmethod
    def telem(name):
        return lambda self: self.vehicle.tlm_value(name)

    @property
    def vehicle(self):
        return self._vehicle
