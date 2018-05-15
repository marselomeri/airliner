from abc import abstractmethod


class PylinerModule(object):
    def __init__(self, vehicle):
        self.vehicle = vehicle
        for name, path in self.required_telemetry():
            setattr(self, name, property(lambda: self.vehicle.tlm_value(path)))

    @classmethod
    @abstractmethod
    def required_telemetry(cls):
        """Return the required telemetry to enable this module.

        Return:
            Iterable[str, str]: An iterable of telemetry paths required.
        """
        pass
