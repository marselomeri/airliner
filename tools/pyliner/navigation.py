from numbers import Real

import time

import math

from geographic import GeographicWrapper, LatLon
from pyliner_module import PylinerModule
from util import get_time


def constant(value):
    return lambda current, target: value


def proportional(const, neutral=0.5):
    return lambda current, target: (target - current) * const + neutral


class Navigation(PylinerModule):
    """Navigation module. Contains all navigation features.
    
    Note:
        Currently this module takes lateral and vertical navigation as separate
        components, and only executes one at a time. 
    TODO: In a future version a more integrated 3d-space will be implemented.
    """
    def __init__(self):
        super(Navigation, self).__init__()
        self.geographic = GeographicWrapper

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
        return PylinerModule.telem(Navigation.req_telem['altitude'])(self)

    @property
    def coordinate(self):
        return LatLon(self.latitude, self.longitude)

    @property
    def heading(self):
        """Degrees"""
        return math.degrees(self.yaw) % 360

    @property
    def latitude(self):
        """Degrees"""
        return PylinerModule.telem(Navigation.req_telem['latitude'])(self)

    @property
    def longitude(self):
        """Degrees"""
        return PylinerModule.telem(Navigation.req_telem['longitude'])(self)

    @property
    def yaw(self):
        """Radians. North 0 incrementing clockwise. Wrap at Pi (180 degrees)"""
        return PylinerModule.telem(Navigation.req_telem['yaw'])(self)

    def down(self, amount, method=None, tolerance=1):
        self.vnav(by=-amount, method=method, tolerance=tolerance)

    def forward(self, amount, tolerance=1):
        old_coor = self.coordinate

    @classmethod
    def required_telemetry_paths(cls):
        return cls.req_telem.values()

    def up(self, amount, method=None, tolerance=1):
        self.vnav(by=amount, method=method, tolerance=tolerance)

    def vnav(self, by=None, to=None, method=None, tolerance=1):
        if not any((by, to)):
            raise ValueError('Must set either by or to.')
        elif by and to:
            raise ValueError('Cannot set both by and to.')
        if not method:
            raise ValueError('Must have navigation method.')
        if not isinstance(tolerance, Real) or tolerance <= 0:
            raise ValueError('Tolerance must be set to a real positive number.')
        target_altitude = self.altitude + by if by else to
        while (target_altitude - self.altitude) > tolerance:
            new_z = method(self.altitude, target_altitude)
            capped_z = min(max(new_z, -1), 1)
            self.vehicle.fd.z = capped_z
            time.sleep(1 / 32)
        self.vehicle.fd.z = 0.5
