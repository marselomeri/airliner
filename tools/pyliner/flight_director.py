from pyliner_module import PylinerModule
from telemetry import ManualSetpoint


class FlightDirector(PylinerModule):
    # TODO: Limit axis assignment
    def __init__(self, strict_set=False):
        super(FlightDirector, self).__init__()
        self._x = self._y = self._z = self._r = 0.0
        self.strict_set = strict_set

    def __call__(self, x=None, y=None, z=None, r=None):
        if x is not None:
            self.x = x
        if y is not None:
            self.y = y
        if z is not None:
            self.z = z
        if r is not None:
            self.r = r

    def send_telemetry(self):
        mod_z = self.z / 2.0 + 0.5
        # print('Sending Telem: {} {} {} -> {}'.format(round(self.x, 2),
        #                                              round(self.y, 2),
        #                                              round(self.z, 2),
        #                                              round(mod_z, 2)))
        self.vehicle.buffer_telemetry(
            ManualSetpoint(X=self._x, Y=self._y, Z=mod_z, R=self._r,
                           PosctlSwitch=1, GearSwitch=1, ArmSwitch=1))

    @property
    def r(self):
        return self._r

    @r.setter
    def r(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._r = value
        self.send_telemetry()

    @classmethod
    def required_telemetry_paths(cls):
        return None

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._x = value
        self.send_telemetry()

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._y = value
        self.send_telemetry()

    @property
    def z(self):
        return self._z

    @z.setter
    def z(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._z = value
        self.send_telemetry()

    def zero(self):
        self.x = self.y = self.z = self.r = 0.0
        self.send_telemetry()
