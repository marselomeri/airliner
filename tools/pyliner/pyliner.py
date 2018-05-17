#!/usr/bin/python

import time

from base_pyliner import BasePyliner
from communication import Communication
from flight_control_lib import FlightMode
from flight_director import FlightDirector
from navigation import Navigation
from util import LogLevel, get_time


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

    def __init__(self, airliner_map, ci_port, to_port, address='localhost',
                 script_name=None, log_dir=None, failure_callback=None):
        """Create an instance of Pyliner.

        Args:
            script_name (str): The script currently being executed. Used for
                generating log file names.
            log_dir (str): The directory that log files will be saved to.
                Defaults to *pyliner*/logs.
        """
        super(Pyliner, self).__init__(script_name=script_name, log_dir=log_dir)

        # Default modules
        self.enable_module('com', Communication(
            address=address,
            airliner_map=airliner_map,
            ci_port=ci_port,
            to_port=to_port))
        self.enable_module('fd', FlightDirector())
        self.enable_module('nav', Navigation())

        self.failure_callback = failure_callback

    def critical_failure(self, exc_type, exc_val, exc_tb):
        if self.failure_callback is not None:
            self.failure_callback(self, (exc_type, exc_val, exc_tb))

    def wait_clean(self):
        while self.com.send_dirty:
            time.sleep(1 / 32)

    def arm(self):
        print("%s: Arming vehicle" % self.script_name)
        self.log("Arming vehicle")
        self.com.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.0},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 0},
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 0},
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 0},
                 {'name': 'GearSwitch', 'value': 0},
                 {'name': 'ArmSwitch', 'value': 3},  # OFF
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})
        self.wait_clean()
        self.com.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.0},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 0},
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 0},
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 0},
                 {'name': 'GearSwitch', 'value': 0},
                 {'name': 'ArmSwitch', 'value': 1},  # ON
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})
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
            out (Any): If not None, print this every loop.
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
        self.com.subscribe({'tlm': module.required_telemetry_paths()})

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
        self.com.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.5},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 0},
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 1},  # ON
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 0},
                 {'name': 'GearSwitch', 'value': 1},
                 {'name': 'ArmSwitch', 'value': 0},
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})

    def takeoff(self):
        print("%s: Auto takeoff" % self.script_name)
        self.log("Auto takeoff")
        self.com.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.0},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 0},
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 0},
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 1},  # ON
                 {'name': 'GearSwitch', 'value': 0},
                 {'name': 'ArmSwitch', 'value': 1},
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})
        time.sleep(5)

    def tlm(self, tlm):
        """ Get all data of specified telemetry item

        Args:
            tlm (str): Operational name of requested telemetry

        Returns:
            Telemetry data dict or None if not found
        """
        if tlm not in self.telemetry:
            return None
        else:
            return self.com.telemetry[tlm]

    def tlm_value(self, tlm):
        """ Get current value of specified telemetry item

        Args:
            tlm (str): Operational name of requested telemetry

        Returns:
            Current value of telemetry or None if not found
        """
        if tlm not in self.com.telemetry:
            return None
        else:
            return self.com.telemetry[tlm]['value']

    def rtl(self):
        print("%s: RTL" % self.script_name)
        self.log("RTL")
        self.com.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.0},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 1},  # ON
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 0},
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 0},
                 {'name': 'GearSwitch', 'value': 3},
                 {'name': 'ArmSwitch', 'value': 1},
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})
        self.wait_clean()
