import time

from flufl.enum import Enum

from app import App
from pyliner_exceptions import UnauthorizedAtpError
from telemetry import ManualSetpoint
from util import query_yes_no, LogLevel

_WAIT_TIME = 0.1


class FlightMode(Enum):
    Manual = 1
    AltCtl = 2
    PosCtl = 3
    RTL = 4


class Controller(App):
    def __init__(self):
        super(Controller, self).__init__()
        self.atp_override = None
        self._telemetry = None

    def arm(self):
        """Arm vehicle."""
        print("%s: Arming vehicle" % self.vehicle.script_name)
        self.vehicle.log("Arming vehicle")
        self._telemetry = ManualSetpoint(ArmSwitch=3)
        self._wait_clean()
        self._telemetry = ManualSetpoint(ArmSwitch=1)
        self._wait_clean()

    def atp(self, text, error=True):
        """Collect authorization to proceed (ATP) from the user."""
        atp_auth = None
        while atp_auth is None:
            if callable(self.atp_override):
                atp_auth = self.atp_override()
            elif self.atp_override is not None:
                atp_auth = self.atp_override
            else:
                atp_auth = query_yes_no(
                    "{} requires authorization for: {}".format(
                        self.vehicle.script_name, text))
            self.vehicle.log("{} ATP: {} Auth: {}".format(
                self.vehicle.script_name, text, atp_auth))
            # if atp_auth == 'takeover':
            #     try:
            #         code.interact(
            #             banner='Entering ATP local override mode.\nAccess vehicle '
            #                    'using "self". ex. self.nav.position\nExit '
            #                    'interactive mode via Ctrl+D.', local=locals())
            #     except SystemExit:
            #         pass
            #     atp_auth = None
            if error and atp_auth is False:
                raise UnauthorizedAtpError
            return atp_auth

    def disarm(self):
        print("%s: Disarming vehicle" % self.vehicle.script_name)
        self.vehicle.log("Disarming vehicle")
        self._telemetry = ManualSetpoint(ArmSwitch=3)
        self._wait_clean()

    def flight_mode(self, mode):
        if not mode:
            self.vehicle.log("Mode transition requires a passed mode.",
                             LogLevel.Error)
        if mode == FlightMode.Manual:
            raise NotImplemented()
        elif mode == FlightMode.AltCtl:
            raise NotImplemented()
        elif mode == FlightMode.PosCtl:
            self._mode_posctl()
        self._wait_clean()

    def _mode_posctl(self):
        print("%s: Position control" % self.vehicle.script_name)
        self.vehicle.log("Position control")
        self._telemetry = ManualSetpoint(Z=0.5, PosctlSwitch=1, GearSwitch=1)
        self._wait_clean()

    @classmethod
    def required_telemetry_paths(cls):
        return None

    def rtl(self):
        """Return to launch."""
        print("%s: RTL" % self.vehicle.script_name)
        self.vehicle.log("RTL")
        self._telemetry = ManualSetpoint(ReturnSwitch=1, GearSwitch=3, ArmSwitch=1)
        self._wait_clean()

    def takeoff(self):
        """Takeoff"""
        print("%s: Auto takeoff" % self.vehicle.script_name)
        self.vehicle.log("Auto takeoff")
        self._telemetry = ManualSetpoint(TransitionSwitch=1, ArmSwitch=1)
        self._wait_clean()
        time.sleep(5)

    @property
    def telemetry(self):
        t = self._telemetry
        self._telemetry = None
        return t

    @property
    def telemetry_available(self):
        return self._telemetry is not None

    def _wait_clean(self):
        while self.telemetry_available:
            time.sleep(_WAIT_TIME)
