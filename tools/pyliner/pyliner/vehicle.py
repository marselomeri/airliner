"""
The Vehicle module provides the user with a concrete implementation of
BaseVehicle, with some useful modules and settings pre-loaded. The user is free
to not use Vehicle in favor of a completely custom subclass of BaseVehicle.

Classes:
    Vehicle  A vehicle for the user to control.
"""

from pyliner.app.geographic_app import GeographicApp
from pyliner.app.time_app import TimeApp
from pyliner.base_vehicle import BaseVehicle
from pyliner.app.controller import Controller
from pyliner.app.flight_director import FlightDirector
from pyliner.app.geofence import Geofence, LayerKind
from pyliner.app.navigation.navigation import Navigation


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
        geographic = geographic or GeographicApp()
        time = time or TimeApp()
        geofence = Geofence()
        navigation = Navigation()

        # Attach defaults
        self.attach_app(communications)
        self.attach_app(geographic)
        # self.attach_service(time)
        self.attach_app(geofence)
        self.attach_app(Controller())
        self.attach_app(FlightDirector())
        self.attach_app(navigation)

        # Add helpful default settings
        geofence.add_layer(0, 'base', LayerKind.ADDITIVE)
        navigation.defaults.update({'timeout': None, 'underflow': 5.0})
