#!/usr/bin/python

import time

from flufl.enum import Enum

from base_pyliner import BasePyliner
from communication import Communication
from flight_director import FlightDirector
from navigation import Navigation
from telemetry import ManualSetpoint
from util import LogLevel


__version__ = 0.1


class FlightMode(Enum):
    Manual = 1
    AltCtl = 2
    PosCtl = 3
    RTL = 4


DEFAULT_CI_PORT = 5008
DEFAULT_TO_PORT = 5011


class Pyliner(BasePyliner):
    """Represents a vehicle that the user may control.

    The basic modules that a vehicle presents are:
        com (Communication): Provides methods to communicate with the physical
            vehicle in the air.
        fd (FlightDirector): Provides methods for controlling the raw x, y, z,
            and rotation axes of the vehicle.
        nav (Navigation): Provides methods for controlling the direction and
            speed of the vehicle.

    The user is free to replace the defaults of these modules in the constructor
    but it is highly recommended that replacements implement or subclass the
    default modules. TODO Implement replacing in constructor
    """

    def __init__(self, airliner_map, address='localhost',
                 ci_port=DEFAULT_CI_PORT, to_port=DEFAULT_TO_PORT,
                 script_name=None, log_dir=None, failure_callback=None):
        """Create an instance of Pyliner.

        Args:
            airliner_map (dict): Airliner Mapping, typically read from a JSON.
            address (str): Address to connect to vehicle.
            ci_port (int):
            to_port (int):
            script_name (str): The script currently being executed. Used for
                generating log file names.
            log_dir (str): The directory that log files will be saved to.
                Defaults to *pyliner*/logs.
            failure_callback (Callable[[Pyliner, Tuple], None]): Function
                handle that will be invoked on a failure of the controlling
                script.
        """
        super(Pyliner, self).__init__(
            communications=Communication(
                airliner_map=airliner_map,
                address=address,
                ci_port=ci_port,
                to_port=to_port),
            script_name=script_name,
            log_dir=log_dir)

        # Default modules
        self.enable_module('fd', FlightDirector())
        self.enable_module('nav', Navigation())

        self.failure_callback = failure_callback

    def critical_failure(self, exc_type, exc_val, exc_tb):
        if self.failure_callback is not None:
            self.failure_callback(self, (exc_type, exc_val, exc_tb))

    def wait_clean(self):
        while self._communications.send_dirty:
            time.sleep(1 / 32)

    def arm(self):
        print("%s: Arming vehicle" % self.script_name)
        self.log("Arming vehicle")
        self.buffer_telemetry(ManualSetpoint(ArmSwitch=3))
        self.wait_clean()
        self.buffer_telemetry(ManualSetpoint(ArmSwitch=1))
        self.wait_clean()

    def atp(self, txt):
        print("%s requires authorization for: %s" % (self.script_name, txt))
        raw_input("Press enter to proceed >>>")
        self.log("%s requires authorization to proceed. Requesting: %s" % (
            self.script_name, txt))

    def await_fresh(self, tlm, poll=1.0, out=None):
        """Loop until the telemetry value changes. This is blocking.

        Args:
            tlm (str): The telemetry to monitor.
            poll (float): Check every `poll` seconds.
            out (Callable[[], None]): If not None, print this every loop.
        """
        old_val = self.tlm_value(tlm)
        while self.tlm_value(tlm) == old_val:
            if out is not None:
                out()
            time.sleep(poll)
        return self.tlm_value(tlm)

    def enable_module(self, name, module):
        """
        Enable a Pyliner Module on this vehicle. All required telemetry for the
        new module will be subscribed to.

        Args:
            name (str): The name that the module will be initialized under.
            module (Type[PylinerModule]): The module to enable.
        """
        super(Pyliner, self).enable_module(name, module)
        self._communications.subscribe({'tlm': module.required_telemetry_paths()})

    def disarm(self):
        print("%s: Disarming vehicle" % self.script_name)
        self.log("Disarming vehicle")
        self.send_telemetry(ManualSetpoint(ArmSwitch=3))

    def flight_mode(self, mode):
        if not mode:
            self.log("Mode transition requires a passed mode.",
                     LogLevel.Error)
        if mode == FlightMode.Manual:
            raise NotImplemented()
        elif mode == FlightMode.AltCtl:
            raise NotImplemented()
        elif mode == FlightMode.PosCtl:
            self.mode_posctl()
        self.wait_clean()

    def mode_posctl(self):
        print("%s: Position control" % self.script_name)
        self.log("Position control")
        self.buffer_telemetry(
            ManualSetpoint(Z=0.5, PosctlSwitch=1, GearSwitch=1))

    def takeoff(self):
        print("%s: Auto takeoff" % self.script_name)
        self.log("Auto takeoff")
        self.buffer_telemetry(ManualSetpoint(TransitionSwitch=1, ArmSwitch=1))
        time.sleep(5)

    def tlm(self, tlm):
        """ Get all data of specified telemetry item.

        Args:
            tlm (str): Operational name of requested telemetry.

        Returns:
            dict: Telemetry data.

        Raises:
            KeyError: If telemetry is not found.
        """
        return self._communications.telemetry[tlm]

    def tlm_value(self, tlm):
        """ Get current value of specified telemetry item.

        Args:
            tlm (str): Operational name of requested telemetry.

        Returns:
            Any: Current value of telemetry.

        Raises:
            KeyError: If telemetry is not found.
        """
        return self.tlm(tlm)['value']

    def rtl(self):
        print("%s: RTL" % self.script_name)
        self.log("RTL")
        self.buffer_telemetry(
            ManualSetpoint(ReturnSwitch=1, GearSwitch=3, ArmSwitch=1))
        self.wait_clean()
