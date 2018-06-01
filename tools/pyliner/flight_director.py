from app import App
from telemetry import ManualSetpoint


class FlightDirector(App):
    def __init__(self, strict_set=False):
        super(FlightDirector, self).__init__()
        self._x = self._y = self._z = self._r = 0.0
        self.strict_set = strict_set
        self._telemetry = None

    def __call__(self, x=None, y=None, z=None, r=None):
        if x is not None:
            self.x = x
        if y is not None:
            self.y = y
        if z is not None:
            self.z = z
        if r is not None:
            self.r = r

    def _send_telemetry(self):
        mod_z = self.z / 2.0 + 0.5
        self._telemetry = ManualSetpoint(X=self._x, Y=self._y, Z=mod_z,
                                         R=self._r, PosctlSwitch=1,
                                         GearSwitch=1, ArmSwitch=1)

    @property
    def r(self):
        return self._r

    @r.setter
    def r(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._r = value
        self._send_telemetry()

    @classmethod
    def required_telemetry_paths(cls):
        return None

    @property
    def telemetry(self):
        t = self._telemetry
        self._telemetry = None
        return t

    @property
    def telemetry_available(self):
        return self._telemetry is not None

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._x = value
        self._send_telemetry()

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._y = value
        self._send_telemetry()

    @property
    def z(self):
        return self._z

    @z.setter
    def z(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._z = value
        self._send_telemetry()

    def zero(self):
        self.x = self.y = self.z = self.r = 0.0
        self._send_telemetry()
