#!/usr/bin/python

import time

from app import App
from base_pyliner import BasePyliner
from communication import Communication
from controller import Controller
from flight_director import FlightDirector
from geofence import Geofence, LayerKind
from geographic import Geographic
from navigation import Navigation
from telemetry import ManualSetpoint

__version__ = 0.1

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
                Defaults to *PylinerDirectory*/logs.
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

        self.atp_override = None
        self.failure_callback = failure_callback
        self.geographic = Geographic()

        # Default modules
        self.enable_app(0, 'fence', Geofence())
        self.enable_app(1, 'ctrl', Controller())
        self.enable_app(2, 'fd', FlightDirector())
        self.enable_app(3, 'nav', Navigation(self.geographic))

        # Add helpful default settings
        self.fence.add_layer(0, 'base', LayerKind.ADDITIVE)

    def await_change(self, tlm, poll=1.0, out=None):
        """Block until the telemetry value changes.

        Args:
            tlm (str): The telemetry to monitor.
            poll (float): Check every `poll` seconds.
            out (Callable): If not None, call this every loop.
        """
        old_val = self.tlm_value(tlm)
        while self.tlm_value(tlm) == old_val:
            if out is not None:
                out()
            time.sleep(poll)
        return self.tlm_value(tlm)

    def critical_failure(self, exc_type, exc_val, exc_tb):
        if self.failure_callback is not None:
            self.failure_callback(self, (exc_type, exc_val, exc_tb))

    def disarm(self):
        print("%s: Disarming vehicle" % self.script_name)
        self.log("Disarming vehicle")
        self.send_telemetry(ManualSetpoint(ArmSwitch=3))

    def enable_app(self, priority, name, app):
        """
        Enable a Pyliner Module on this vehicle. All required telemetry for the
        new module will be subscribed to.

        Args:
            name (str): The name that the module will be initialized under.
            app (App): The app to enable.
        """
        super(Pyliner, self).enable_app(priority, name, app)
        required_ops = app.required_telemetry_paths()
        if required_ops:
            self._communications.subscribe({'tlm': required_ops})

    def tlm(self, tlm):
        """ Get all data of specified telemetry item.

        Args:
            tlm (str): Operational name of requested telemetry.

        Returns:
            dict: Telemetry data.

        Raises:
            KeyError: If telemetry is not found.
        """
        # TODO Rename variable
        return self._communications._telemetry[tlm]

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
