import math

from pyliner.app import App
from pyliner.navigation.goto import Goto

from pyliner.navigation.heading import Heading
from pyliner.navigation.lnav import Lnav
from pyliner.navigation.rotate import Rotate
from pyliner.navigation.vnav import Vnav
from pyliner.navigation.waypoint import Waypoint


class Navigation(App):
    """Navigation app. Contains all navigation features.

        Note:
            Currently this app takes commands and executes one at a time.
        """
    # TODO: In a future version a more integrated 3d-space will be implemented.
    # TODO Look into using decimal library for precision at any lat/lon

    def __init__(self):
        super(Navigation, self).__init__()
        self._geographic = None
        self._telemetry = None

        self.defaults = {}

    req_telem = {
        'latitude': '/Airliner/CNTL/VehicleGlobalPosition/Lat',
        'longitude': '/Airliner/CNTL/VehicleGlobalPosition/Lon',
        'altitude': '/Airliner/CNTL/VehicleGlobalPosition/Alt',
        'yaw': '/Airliner/CNTL/VehicleGlobalPosition/Yaw',
        'velN': '/Airliner/CNTL/VehicleGlobalPosition/VelN',
        'velE': '/Airliner/CNTL/VehicleGlobalPosition/VelE',
        'velD': '/Airliner/CNTL/VehicleGlobalPosition/VelD'
    }

    # Public Navigation Properties
    @property
    def altitude(self):
        """meters"""
        return App._telem(self.req_telem['altitude'])(self)

    @property
    def heading(self):
        """Degrees"""
        # TODO add setter for property
        return Heading(math.degrees(self.yaw))

    @property
    def latitude(self):
        """Degrees"""
        return App._telem(self.req_telem['latitude'])(self)

    @property
    def longitude(self):
        """Degrees"""
        return App._telem(self.req_telem['longitude'])(self)

    @property
    def position(self):
        """The spatial state of the vehicle."""
        return Waypoint(self.latitude, self.longitude,
                        self.altitude, self.heading)

    @property
    def yaw(self):
        """The vehicle yaw in clockwise radians from north."""
        return App._telem(self.req_telem['yaw'])(self)

    def attach(self, vehicle):
        super(Navigation, self).attach(vehicle)
        self._geographic = vehicle.sensor('geographic')

    def detach(self):
        super(Navigation, self).detach()
        self._geographic = None

    def goto(self, **kwargs):
        return Goto(self, **kwargs)

    def lnav(self, **kwargs):
        return Lnav(self, **kwargs)

    @classmethod
    def required_telemetry_paths(cls):
        return cls.req_telem.values()

    def rotate(self, **kwargs):
        return Rotate(self, **kwargs)

    @property
    def telemetry(self):
        t = self._telemetry
        self._telemetry = None
        return t

    @property
    def telemetry_available(self):
        return self._telemetry is not None

    def vnav(self, **kwargs):
        return Vnav(self, **kwargs)