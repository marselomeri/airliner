from collections import Iterable
from abc import abstractmethod


class PylinerModule(object):
    def __init__(self, vehicle):
        self.vehicle = vehicle

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
