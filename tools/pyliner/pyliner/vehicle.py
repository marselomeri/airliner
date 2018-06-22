"""
The Vehicle module provides the user with a concrete implementation of
BaseVehicle, with some useful modules and settings pre-loaded. The user is free
to not use Vehicle in favor of a completely custom subclass of BaseVehicle.

Classes:
    Vehicle  A vehicle for the user to control.
"""

from app import App
from base_vehicle import BaseVehicle
from controller import Controller
from flight_director import FlightDirector
from geofence import Geofence, LayerKind
from navigation import Navigation


class Vehicle(BaseVehicle):
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

    def __init__(self, vehicle_id, communication):
        """Create an instance of Pyliner.

        Args:
            vehicle_id: Vehicle ID. Should be unique.
            communication: Communications App
        """
        super(Vehicle, self).__init__(vehicle_id, communication)

        self.atp_override = None

        # Default components
        self.attach_app(0, 'fence', Geofence())
        self.attach_app(1, 'ctrl', Controller())
        self.attach_app(2, 'fd', FlightDirector())
        self.attach_app(3, 'nav', Navigation())

        # Add helpful default settings
        self.apps['fence'].add_layer(0, 'base', LayerKind.ADDITIVE)
        self.apps['nav'].defaults.update({'timeout': None, 'underflow': 5.0})

    def attach_app(self, priority, app_name, app):
        """
        Enable a Pyliner Module on this vehicle. All required telemetry for the
        new module will be subscribed to.

        Args:
            priority: The priority that the app communicates with the vehicle.
            app_name (str): The name that the module will be initialized under.
            app (App): The app to enable.
        """
        super(Vehicle, self).attach_app(priority, app_name, app)
        required_ops = app.required_telemetry_paths()
        if required_ops:
            self.communications.subscribe({'tlm': required_ops})
