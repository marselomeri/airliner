"""
The Flight Director app provides a Flight Director Application to control a
vehicle's basic axes of motion.

Apps:
    FlightDirector  Grants the user control of a vehicle's basic axes.
"""

from pyliner.app import App
from pyliner.action import ACTION_AXIS_SET, ACTION_SEND_COMMAND, \
    ACTION_AXIS_ZERO
from pyliner.intent import Intent, IntentFilter
from pyliner.telemetry import ManualSetpoint


class FlightDirector(App):
    """The FlightDirector allows for manual, direct control of a vehicle's axes.

     The X, Y, Z, and Yaw (R) axes are controlled via a ManualSetpoint command.
     """
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

    def attach(self, vehicle_wrapper):
        super(FlightDirector, self).attach(vehicle_wrapper)
        self.vehicle.add_filter(
            IntentFilter(actions=[ACTION_AXIS_SET]),
            self.axis_set
        )
        self.vehicle.add_filter(
            IntentFilter(actions=[ACTION_AXIS_ZERO]),
            lambda i: self.zero()
        )

    def detach(self):
        self.vehicle.callback = None
        super(FlightDirector, self).detach()

    @property
    def qualified_name(self):
        return 'com.windhover.pyliner.app.flight_director'

    def axis_set(self, intent):
        axis, value = intent.data
        self(**{axis: value})

    def _send_telemetry(self):
        mod_z = self.z / 2.0 + 0.5  # [-1, 1] -> [0, 1]
        # self.debug('Sending Telemetry: {} {} {} {}'.format(
        #     self.x, self.y, mod_z, self.r))
        with self.control_block() as block:
            block.broadcast(Intent(
                action=ACTION_SEND_COMMAND,
                data=block.request(ManualSetpoint(
                    X=self._x, Y=self._y, Z=mod_z, R=self._r,
                    PosctlSwitch=1, GearSwitch=1, ArmSwitch=1))))

    def zero(self):
        self._x = self._y = self._z = self._r = 0.0
        self._send_telemetry()

    @property
    def r(self):
        return self._r

    @r.setter
    def r(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign R outside of [-1, 1].')
        self._r = value
        self._send_telemetry()

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign X outside of [-1, 1].')
        self._x = value
        self._send_telemetry()

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign Y outside of [-1, 1].')
        self._y = value
        self._send_telemetry()

    @property
    def z(self):
        return self._z

    @z.setter
    def z(self, value):
        if self.strict_set and (value > 1 or value < -1):
            raise ValueError('Cannot assign Z outside of [-1, 1].')
        self._z = value
        self._send_telemetry()
