from commands import ManualSetpoint
from pyliner_module import PylinerModule
from util import get_time


class FlightDirector(PylinerModule):
    # TODO: Limit axis assignment
    def __init__(self):
        super(FlightDirector, self).__init__()
        self._x = self._y = self._z = self._r = 0.0

    def send_telemetry(self):
        mod_z = self.z / 2.0 + 0.5
        # print('Sending Telem: {} {} {} -> {}'.format(round(self.x, 2),
        #                                              round(self.y, 2),
        #                                              round(self.z, 2),
        #                                              round(mod_z, 2)))
        self.vehicle.com.send_telemetry(
            ManualSetpoint(X=self._x, Y=self._y, Z=mod_z, R=self._r,
                           PosctlSwitch=1, GearSwitch=1, ArmSwitch=1))

    @property
    def r(self):
        return self._r

    @r.setter
    def r(self, value):
        self._r = value
        self.send_telemetry()

    @classmethod
    def required_telemetry_paths(cls):
        return []

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        self._x = value
        self.send_telemetry()

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        self._y = value
        self.send_telemetry()

    @property
    def z(self):
        return self._z

    @z.setter
    def z(self, value):
        self._z = value
        self.send_telemetry()

    def zero(self):
        self._x = self._y = self._z = self._r = 0
        self.send_telemetry()
