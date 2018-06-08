import math
import re
import time
from abc import abstractmethod
from collections import Iterable
from numbers import Real

from datetime import datetime

from app import App
from position import Position
from pyliner_exceptions import CommandTimeout
from telemetry import SetpointTriplet
from util import shifter, copy_update, Loggable, OverlayDict

_NAV_SLEEP = 1.0/16.0


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


NotSet = object()
"""Indicate a kwarg that is not set (different than None). Use responsibly.
You probably shouldn't re-assign this."""


class NavigationFactory(Loggable):
    def __init__(self, navigation, **kwargs):
        super(NavigationFactory, self).__init__(navigation.vehicle.logger)
        self._nav = navigation
        self._default = OverlayDict(kwargs, self._nav.defaults)

    @abstractmethod
    def __call__(self, **kwargs):
        raise NotImplementedError

    def resolve(self, item, name):
        return item if item is not NotSet else self._default[name]


class Lnav(NavigationFactory):
    def __call__(self, distance, axis=NotSet, method=NotSet, tolerance=NotSet,
                 timeout=NotSet):
        """Perform a lateral movement.

        Block until the distance traveled is within the tolerance of the target
        distance.

        Args:
            distance (Real): Distance in meters to move.
            axis (str): Must be one of the lateral movement axes (x, y, or z),
                and may be prefixed by an optional "-" for negative movement.
            method (Callable[[Real, Real], Real]): Callable takes two arguments,
                the distance traveled and the target distance, and returns an
                axis control value within [-1, 1].
            tolerance (Real): The allowable error in movement before the method
                sets the control to 0 and returns.
        """
        # Default resolution
        axis = self.resolve(axis, 'axis')
        method = self.resolve(method, 'method')
        tolerance = self.resolve(tolerance, 'tolerance')
        timeout = self.resolve(timeout, 'timeout')

        # Sanity checks
        if not method or not callable(method):
            raise ValueError('Must have a callable navigation method.')
        if not isinstance(tolerance, Real) or tolerance <= 0:
            raise ValueError('Tolerance must be set to a positive real number.')
        if not isinstance(timeout, Real) or timeout <= 0:
            raise ValueError('Timeout must be set to a positive real number.')

        # Match axis value
        axis_match = re.match('(-)?([xyz])', axis)
        if not axis_match: raise ValueError('Axis must match "(-)?([xyz])".')
        neg, axis = axis_match.groups()

        # Timeout
        # TODO Use vehicle time not local
        if timeout is None:
            timeout = datetime.max
        else:
            timeout += datetime.now()

        original = self._nav.position
        while datetime.now() < timeout:
            delta = self._nav._geographic.distance(original, self._nav.position)
            if (distance - delta) < tolerance:
                self.info('lnav expected %s actual %s (%s < %s m)',
                          distance, delta, distance - delta, tolerance)
                setattr(self._nav.vehicle.app('fd'), axis, 0.0)
                return self
            control = method(delta, distance)
            self.debug('lnav expected %.3f actual %.3f (%.3f < %.3f m) %.3f',
                       distance, delta, distance - delta, tolerance, control)
            setattr(self._nav.vehicle.app('fd'), axis,
                    -control if neg else control)
            time.sleep(_NAV_SLEEP)
        raise CommandTimeout('lnav exceeded timeout')

    def backward(self, distance, **kwargs):
        """Move backward by a distance. See lnav for full documentation."""
        return self(distance, '-x', **kwargs)
        
    def forward(self, distance, **kwargs):
        """Move forward by a distance. See lnav for full documentation."""
        return self(distance, 'x', **kwargs)

    def left(self, distance, **kwargs):
        """Move left by a distance. See lnav for full documentation."""
        return self(distance, '-y', **kwargs)

    def right(self, distance, **kwargs):
        """Move right by a distance. See lnav for full documentation."""
        return self(distance, 'y', **kwargs)


class Rotate(NavigationFactory):
    def __call__(self, **kwargs):
        super(Rotate, self).__call__()

    def clockwise(self, degrees, method=NotSet, tolerance=NotSet,
                  timeout=NotSet):
        """Rotate clockwise by a number of degrees."""
        # Default resolution
        method = self.resolve(method, 'method')
        tolerance = self.resolve(tolerance, 'tolerance')
        timeout = self.resolve(timeout, 'timeout')

        old_heading = self._nav.heading
        target_heading = (old_heading + degrees) % 360
        min_tol = (target_heading - tolerance) % 360

        def unroll_heading():
            return self._nav.heading if self._nav.heading < target_heading \
                else self._nav.heading - 360

        while unroll_heading() < min_tol:
            self._nav.vehicle.app('fd').r = method(unroll_heading(), target_heading)
            time.sleep(_NAV_SLEEP)
        self.info('clockwise expected %s actual %s (%s > %s)', target_heading,
                  unroll_heading(), unroll_heading(), min_tol)
        self._nav.vehicle.app('fd').r = 0.0

    def counterclockwise(self, degrees, method=None, tolerance=None):
        """Rotate counterclockwise by a number of degrees."""
        method = method if method else self.resolve('method')
        tolerance = tolerance if tolerance is not None \
            else self.resolve('tolerance')

        old_heading = self._nav.heading
        target_heading = (old_heading - degrees) % 360
        max_tol = (target_heading + tolerance) % 360

        def unroll_heading():
            return self._nav.heading if self._nav.heading > target_heading \
                else self._nav.heading + 360

        while unroll_heading() > max_tol:
            self._nav.vehicle.app('fd').r = method(unroll_heading(), target_heading)
            time.sleep(_NAV_SLEEP)
        self.info('counterclockwise expected %s actual %s (%s < %s)',
                  target_heading, unroll_heading(), unroll_heading(), max_tol)
        self._nav.vehicle.app('fd').r = 0.0


class Goto(NavigationFactory):
    def __call__(self, waypoints, tolerance=None):
        """Move the vehicle to a waypoint or along a series of waypoints.

        Block until the vehicle is within tolerance of the final waypoint.
        """
        tolerance = tolerance if tolerance is not None \
            else self.resolve('tolerance')
        if not isinstance(tolerance, Real) or tolerance <= 0:
            raise ValueError('Tolerance must be set to a positive real number.')

        if not isinstance(waypoints, Iterable):
            waypoints = (waypoints,)
        for prv, cur, nxt in shifter(3, (None,) + waypoints + (None,)):
            palt = 0 if not prv else prv.altitude \
                if prv.altitude is not None else self._nav.altitude
            calt = 0 if not cur else cur.altitude \
                if cur.altitude is not None else self._nav.altitude
            nalt = 0 if not nxt else nxt.altitude \
                if nxt.altitude is not None else self._nav.altitude
            pyaw = 0 if not prv else prv.yaw \
                if prv.yaw is not None else self._nav.yaw
            cyaw = 0 if not cur else cur.yaw \
                if cur.yaw is not None else self._nav.yaw
            nyaw = 0 if not nxt else nxt.yaw \
                if nxt.yaw is not None else self._nav.yaw
            self._nav._telemetry = SetpointTriplet(
                Prev_Lat=prv.latitude if prv is not None else 0,
                Prev_Lon=prv.longitude if prv is not None else 0,
                Prev_Alt=palt, Prev_Yaw=pyaw,
                Prev_Valid=prv is not None, Prev_PositionValid=prv is not None,
                Cur_Lat=cur.latitude if cur is not None else 0,
                Cur_Lon=cur.longitude if cur is not None else 0,
                Cur_Alt=calt, Cur_Yaw=cyaw,
                Cur_Valid=cur is not None, Cur_PositionValid=cur is not None,
                Next_Lat=nxt.latitude if nxt is not None else 0,
                Next_Lon=nxt.longitude if nxt is not None else 0,
                Next_Alt=nalt, Next_Yaw=nyaw,
                Next_Valid=nxt is not None, Next_PositionValid=nxt is not None
            )
            while True:
                distance = self._nav._geographic.distance(cur, self._nav.position)
                if distance < tolerance:
                    self._nav.vehicle.info(
                        'goto expected %s actual %s (%s < %s m)',
                        cur, self._nav.position, distance, tolerance)
                    break
                time.sleep(_NAV_SLEEP)


class Vnav(NavigationFactory):
    def __call__(self, by=None, to=None, method=None, tolerance=None):
        """Perform a vertical navigation.

        Blocks until the vehicle altitude is within tolerance of the target
        change or absolute altitude.

        Args:
            by (Real): Change altitude by this amount. May be negative. Cannot
                be set at the same time as `to`.
            to (Real): Ascend or descend to this altitude. Cannot be set at the
                same time as `by`.
            method (Callable[[Real, Real], Real]): Take two arguments, the
                current altitude and the target altitude, and return an
                axis control value within [-1, 1].
            tolerance (Real): The allowable error in altitude before the method
                sets the z-axis to 0 and returns.
        """
        if not any((by, to)):
            raise ValueError('Must set either by or to.')
        elif by and to:
            raise ValueError('Cannot set both by and to.')
        if not method or not callable(method):
            raise ValueError('Must have a callable navigation method.')
        if not isinstance(tolerance, Real) or tolerance <= 0:
            raise ValueError('Tolerance must be set to a positive real number.')

        target_altitude = (self._nav.altitude + by) if by else to
        while abs(target_altitude - self._nav.altitude) > tolerance:
            control = method(self._nav.altitude, target_altitude)
            self.debug('vnav expected %.3f actual %.3f (%.3f < %.3f m) %.3f',
                       target_altitude, self._nav.altitude,
                       target_altitude - self._nav.altitude, tolerance, control)
            self._nav.vehicle.app('fd').z = control
            time.sleep(_NAV_SLEEP)
        self.info('vnav expected %s actual %s (%s < %s m)', target_altitude,
                  self._nav.altitude, abs(target_altitude - self._nav.altitude),
                  tolerance)
        self._nav.vehicle.app('fd').z = 0.0
        return self

    def down(self, distance, **kwargs):
        """Move down by a distance. See vnav for full documentation."""
        return self(by=-distance, **copy_update(self.kwargs, kwargs))

    def to(self, altitude, **kwargs):
        """Climb or descend to altitude. See vnav for full documentation."""
        return self(to=altitude, **copy_update(self.kwargs, kwargs))

    def up(self, distance, **kwargs):
        """Move up by a distance. See vnav for full documentation."""
        return self(by=distance, **copy_update(self.kwargs, kwargs))


class Navigation(App):
    """Navigation module. Contains all navigation features.

    Note:
        Currently this module takes lateral and vertical navigation as separate
        components, and only executes one at a time.
    TODO: In a future version a more integrated 3d-space will be implemented.
    """

    def __init__(self):
        super(Navigation, self).__init__()
        self._geographic = None
        self._telemetry = None

        self.defaults = {
            'method': None, 'tolerance': None
        }

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
        return self.yaw % 360  # mod is for negative degrees.

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
        return math.degrees(App._telem(self.req_telem['yaw'])(self))

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
