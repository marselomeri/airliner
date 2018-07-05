import math

from pyliner.action import ACTION_TELEM
from pyliner.app import App
from pyliner.intent import Intent
from pyliner.app.navigation.goto import Goto

from pyliner.app.navigation import Heading
from pyliner.app.navigation.lnav import Lnav
from pyliner.app.navigation.rotate import Rotate
from pyliner.app.navigation import Vnav
from pyliner.app.navigation.waypoint import Waypoint
from pyliner.util.conversions import hertz


class Navigation(App):
    """Navigation app. Contains all navigation features.

    Note:
        Currently this app takes commands and executes one at a time.
    """
    # TODO: In a future version a more integrated 3d-space will be implemented.
    # TODO Look into using decimal library for precision at any lat/lon

    def __init__(self):
        super(Navigation, self).__init__()

        self.defaults = {}
        self.sleep_time = hertz(10.0)
        self.telemetry = None

    def attach(self, vehicle_wrapper):
        super(Navigation, self).attach(vehicle_wrapper)
        intent = self.vehicle.broadcast(Intent(
            action=ACTION_TELEM,
            data={
                'altitude': '/Airliner/CNTL/VehicleGlobalPosition/Alt',
                'latitude': '/Airliner/CNTL/VehicleGlobalPosition/Lat',
                'longitude': '/Airliner/CNTL/VehicleGlobalPosition/Lon',
                'yaw': '/Airliner/CNTL/VehicleGlobalPosition/Yaw'
            })).first()
        self.telemetry = intent.result

    def detach(self):
        self.telemetry = None
        super(Navigation, self).detach()

    @property
    def qualified_name(self):
        return 'com.windhover.pyliner.app.navigation'

    def goto(self, **kwargs):
        return Goto(self, **kwargs)

    def lnav(self, **kwargs):
        return Lnav(self, **kwargs)

    def rotate(self, **kwargs):
        return Rotate(self, **kwargs)

    def vnav(self, **kwargs):
        return Vnav(self, **kwargs)

    @property
    def altitude(self):
        """meters"""
        return self.telemetry['altitude'].value

    @property
    def heading(self):
        """Degrees"""
        return Heading(math.degrees(self.yaw))

    @property
    def latitude(self):
        """Degrees"""
        return self.telemetry['latitude'].value

    @property
    def longitude(self):
        """Degrees"""
        return self.telemetry['longitude'].value

    @property
    def position(self):
        """The spatial state of the vehicle."""
        return Waypoint(
            self.latitude, self.longitude, self.altitude, self.heading)

    @property
    def yaw(self):
        """The vehicle yaw in clockwise radians from north [-Pi, Pi]."""
        return self.telemetry['yaw'].value
