"""
The Vehicle module provides the user with a concrete implementation of
BaseVehicle, with some useful modules and settings pre-loaded. The user is free
to not use Vehicle in favor of a completely custom subclass of BaseVehicle.

Classes:
    Vehicle  A vehicle for the user to control.
"""

from pyliner.app import App
from pyliner.app.geographic_app import GeographicApp
from pyliner.app.time_app import TimeApp
from pyliner.base_vehicle import BaseVehicle
from pyliner.app.controller import Controller
from pyliner.app.flight_director import FlightDirector
from pyliner.geofence import Geofence, LayerKind
from pyliner.navigation.navigation import Navigation


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

    def __init__(self, vehicle_id, communications, geographic=None, time=None,
                 logger=None):
        """Create an instance of Pyliner.

        Args:
            vehicle_id: Vehicle ID. Should be unique.
            communications (Communication): Communication App.
                Not exposed as a public module for direct access, but the user
                is given the option to use a custom class if they desire.
            geographic: If None, defaults to Geographic().
            logger: If None, defaults to 'logging.getLogger(vehicle_id)'.
            time: If None, default to TimeSensor().
        """
        super(Vehicle, self).__init__(vehicle_id, logger)

        # Attributes
        self.atp_override = None

        # Component Defaults
        self.communications = communications  # TODO Remove, use intent
        geographic = geographic or GeographicApp()
        time = time or TimeApp()
        geofence = Geofence()
        navigation = Navigation()

        # Attach defaults
        self.attach_app('comms', communications)
        self.attach_app('geographic', geographic)
        # self.attach_service('time', time)
        self.attach_app('fence', geofence)
        self.attach_app('ctrl', Controller())
        self.attach_app('fd', FlightDirector())
        self.attach_app('nav', navigation)

        # Add helpful default settings
        geofence.add_layer(0, 'base', LayerKind.ADDITIVE)
        navigation.defaults.update({'timeout': None, 'underflow': 5.0})

    def attach_app(self, app_name, app):
        """
        Enable a Pyliner Module on this vehicle. All required telemetry for the
        new module will be subscribed to.

        Args:
            app_name (str): The name that the module will be initialized under.
            app (App): The app to enable.
        """
        super(Vehicle, self).attach_app(app_name, app)
        required_ops = app.required_telemetry_paths()
        if required_ops:
            self.communications.subscribe({'tlm': required_ops})
