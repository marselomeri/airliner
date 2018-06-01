#!/usr/bin/python

import time

from app import App
from base_pyliner import BasePyliner
from controller import Controller
from flight_director import FlightDirector
from geofence import Geofence, LayerKind
from geographic import Geographic
from navigation import Navigation

__version__ = '0.1'


class Pyliner(BasePyliner):
    """Represents a vehicle that the user may control.

    The basic apps that a vehicle presents are:
        com (Communication): Provides methods to communicate with the physical
            vehicle in the air.
        fd (FlightDirector): Provides methods for controlling the raw x, y, z,
            and rotation axes of the vehicle.
        nav (Navigation): Provides methods for controlling the direction and
            speed of the vehicle.

    The user is free to replace the defaults of these apps in the constructor
    but it is highly recommended that replacements subclass the default apps.
    """

    def __init__(self, communication, logging):
        """Create an instance of Pyliner.

        Args:
            communication: Communications App
            logging: Logging App
        """
        super(Pyliner, self).__init__(communications=communication,
                                      logging=logging)

        self.atp_override = None
        self.geographic = Geographic()

        # Default modules
        self.attach_app(0, 'fence', Geofence())
        self.attach_app(1, 'ctrl', Controller())
        self.attach_app(2, 'fd', FlightDirector())
        self.attach_app(3, 'nav', Navigation(self.geographic))

        # Add helpful default settings
        self.apps['fence'].add_layer(0, 'base', LayerKind.ADDITIVE)

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

    def attach_app(self, priority, name, app):
        """
        Enable a Pyliner Module on this vehicle. All required telemetry for the
        new module will be subscribed to.

        Args:
            priority: The priority that the app communicates with the vehicle.
            name (str): The name that the module will be initialized under.
            app (App): The app to enable.
        """
        super(Pyliner, self).attach_app(priority, name, app)
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
