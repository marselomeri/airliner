from pyliner_module import PylinerModule
from util import get_time


class FlightDirector(PylinerModule):
    def __init__(self):
        super(FlightDirector, self).__init__()
        self._x = self._y = self._z = self._r = 0.0

    def send_telemetry(self):
        mod_z = self.z / 2 + 0.5
        telem_dict = {
            'Timestamp': get_time(), 'X': self.x, 'Y': self.y, 'Z': mod_z,
            'R': self.r, 'Flaps': 0.0, 'Aux1': 0.0, 'Aux2': 0.0, 'Aux3': 0.0,
            'Aux4': 0.0, 'Aux5': 0.0, 'ModeSwitch': 0, 'ReturnSwitch': 0,
            'RattitudeSwitch': 0, 'PosctlSwitch': 1, 'LoiterSwitch': 0,
            'AcroSwitch': 0, 'OffboardSwitch': 0, 'KillSwitch': 0,
            'TransitionSwitch': 0, 'GearSwitch': 1, 'ArmSwitch': 1,
            'StabSwitch': 0, 'ManSwitch': 0, 'ModeSlot': 0, 'DataSource': 0
        }
        self.vehicle.com.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [{'name': name, 'value': value} for name, value in
                      telem_dict.items()]})

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
