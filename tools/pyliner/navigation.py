import math
import time
from numbers import Real

from geographic import Geographic
from position import Position
from pyliner_module import PylinerModule
from telemetry import SetpointTriplet


def constant(value):
    return lambda current, target: value


def proportional(const, neutral=0.0):
    return lambda current, target: (target - current) * const + neutral


def limiter(min_val, max_val):
    return lambda val: max(min(val, max_val), min_val)


# TODO Look into using decimal library for precision at any lat/lon


class Waypoint(Position):
    """A container for part of the args to a triplet."""
    def __init__(self, latitude, longitude, altitude, heading):
        super(Waypoint, self).__init__(latitude, longitude, altitude)
        self.heading = heading

    def __repr__(self):
        return '{}({}, {}, {}, {})'.format(
            self.__class__.__name__, self.latitude, self.longitude,
            self.altitude, self.heading)

    @property
    def yaw(self):
        if self.heading is None:
            return None
        return math.radians(self.heading if self.heading < 180
                            else self.heading - 360)


class Navigation(PylinerModule):
    """Navigation module. Contains all navigation features.

    Note:
        Currently this module takes lateral and vertical navigation as separate
        components, and only executes one at a time.
    TODO: In a future version a more integrated 3d-space will be implemented.
    """

    def __init__(self):
        super(Navigation, self).__init__()
        self.geographic = Geographic

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
    def position(self):
        return Waypoint(self.latitude, self.longitude, self.altitude)

    @property
    def yaw(self):
        """Radians. North 0 incrementing clockwise. Wrap at Pi (180 degrees)"""
        return PylinerModule.telem(Navigation.req_telem['yaw'])(self)

    def backward(self, amount, method, tolerance=1):
        self.lnav(amount, 'x', method, tolerance, True)

    def clockwise(self, degrees, method, tolerance=1):
        old_heading = self.heading
        target_heading = (old_heading + degrees) % 360
        min_tol = (target_heading - tolerance) % 360

        def unroll_heading():
            return self.heading if self.heading < target_heading \
                else self.heading - 360
        while unroll_heading() < min_tol:
            rotate = method(unroll_heading(), target_heading)
            self.vehicle.fd.r = rotate
        self.vehicle.fd.r = 0.0

    def counterclockwise(self, degrees, method, tolerance=1):
        old_heading = self.heading
        target_heading = (old_heading - degrees) % 360
        max_tol = (target_heading + tolerance) % 360

        def unroll_heading():
            return self.heading if self.heading > target_heading \
                else self.heading + 360
        while unroll_heading() > max_tol:
            rotate = method(unroll_heading(), target_heading)
            self.vehicle.fd.r = rotate
        self.vehicle.fd.r = 0.0

    def down(self, amount, method=None, tolerance=1):
        self.vnav(by=-amount, method=method, tolerance=tolerance)

    def forward(self, amount, method, tolerance=1):
        self.lnav(amount, 'x', method, tolerance)

    def goto(self, waypoint, tolerance=1):
        # type: (Waypoint) -> None
        self.vehicle.buffer_telemetry(SetpointTriplet(
            Cur_Lat=waypoint.latitude,
            Cur_Lon=waypoint.longitude,
            Cur_Alt=0 if waypoint.altitude is None else waypoint.altitude,
            Cur_Yaw=0 if waypoint.heading is None else waypoint.yaw,
            Cur_Valid=1, Cur_PositionValid=1
        ))
        while self.geographic.distance(waypoint, self.position) > tolerance:
            time.sleep(0.1)

    def left(self, amount, method, tolerance=1):
        self.lnav(amount, 'y', method, tolerance, True)

    def lnav(self, amount, axis, method, tolerance, negate=False):
        old_coor = self.position
        distance = self.geographic.distance(old_coor, self.position)
        while (amount - distance) > tolerance:
            velocity = method(distance, amount)
            setattr(self.vehicle.fd, axis, -velocity if negate else velocity)
            time.sleep(1 / 32)
            distance = self.geographic.distance(old_coor, self.position)
        setattr(self.vehicle.fd, axis, 0.0)

    @classmethod
    def required_telemetry_paths(cls):
        return cls.req_telem.values()

    def right(self, amount, method=None, tolerance=1):
        self.lnav(amount, 'y', method, tolerance)

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
            raise ValueError('Tolerance must be set to a positive real number.')
        target_altitude = (self.altitude + by) if by is not None else to
        while abs(target_altitude - self.altitude) > tolerance:
            new_z = method(self.altitude, target_altitude)
            capped_z = min(max(new_z, -1), 1)
            self.vehicle.fd.z = capped_z
            time.sleep(1 / 32)
        self.vehicle.fd.z = 0.0
