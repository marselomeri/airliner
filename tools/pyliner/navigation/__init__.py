import math
import re
import time
from abc import abstractmethod
from collections import Iterable
from numbers import Real

from datetime import datetime, timedelta

from app import App
from navigation.heading import Direction, Heading
from position import Position
from pyliner_exceptions import CommandTimeout
from telemetry import SetpointTriplet
from util import shifter, Loggable, OverlayDict

_NAV_SLEEP = 1.0 / 16.0


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
        try:
            return item if item is not NotSet else self._default[name]
        except KeyError as e:
            raise KeyError('No default set for unset parameter '
                           '"{}".'.format(name))


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
        # NotSet resolution
        axis = self.resolve(axis, 'axis')
        method = self.resolve(method, 'method')
        tolerance = self.resolve(tolerance, 'tolerance')
        timeout = self.resolve(timeout, 'timeout')

        # Sanity checks
        if not method or not callable(method):
            raise ValueError('Must have a callable navigation method.')
        if not isinstance(tolerance, Real) or tolerance <= 0:
            raise ValueError('Tolerance must be set to a positive real number.')

        # Match axis value
        axis_match = re.match('(-)?([xyz])', axis)
        if not axis_match:
            raise ValueError('Axis must match "(-)?([xyz])".')
        neg, axis = axis_match.groups()

        # Timeout
        # TODO Use vehicle time not local
        timeout = datetime.max if timeout is None else timeout + datetime.now()

        original = self._nav.position
        while datetime.now() < timeout:
            delta = self._nav._geographic.distance(original, self._nav.position)
            if (distance - delta) < tolerance:
                self.info('lnav expected %s actual %s (%s < %s m)',
                          distance, delta, distance - delta, tolerance)
                setattr(self._nav.vehicle.app('fd'), axis, 0.0)
                return self
            control = method(delta, distance)
            control = -control if neg else control
            self.debug('lnav toward %.3f actual %.3f (%.3f < %.3f m) %.3f',
                       distance, delta, distance - delta, tolerance, control)
            setattr(self._nav.vehicle.app('fd'), axis, control)
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
    def __call__(self, by=None, to=None, method=NotSet, tolerance=NotSet,
                 direction=Direction.NEAREST, timeout=NotSet, underflow=NotSet):
        # NotSet resolution
        method = self.resolve(method, 'method')
        tolerance = self.resolve(tolerance, 'tolerance')
        direction = self.resolve(direction, 'direction')
        timeout = self.resolve(timeout, 'timeout')
        underflow = self.resolve(underflow, 'underflow')

        # Sanity checks
        if not by and not to:
            raise ValueError('Must set one of by or to.')
        elif by and to:
            raise ValueError('Must not set both by and to.')
        if not method or not callable(method):
            raise ValueError('Must have a callable navigation method.')
        if not isinstance(tolerance, Real) or tolerance < 0.0:
            raise ValueError('Tolerance must be a non-negative real number.')
        if direction not in Direction:
            raise TypeError('Direction must be a valid Direction.')
        if timeout is not None and not isinstance(timeout, timedelta):
            raise ValueError('Timeout must be None or a timedelta.')
        if not isinstance(underflow, Real) or underflow < 0.0:
            raise ValueError('Underflow must be a non-negative real number.')

        # Timeout
        # TODO Use vehicle time not local
        timeout = datetime.max if timeout is None else datetime.now() + timeout

        original = self._nav.heading
        target = original + by if by else Heading(to)
        tol_range = target.range(tolerance)

        while datetime.now() < timeout:
            current = self._nav.heading
            if current in tol_range:
                self.info('rotate expected %s actual %s (in %s)',
                          target, current, tol_range)
                self._nav.vehicle.app('fd').r = 0.0
                return self
            distance = Heading.distance(current, target, direction, underflow)
            control = method(0.0, distance)
            self.debug('rotate toward %.3f current %.3f (%.3f < %.3f) %.3f',
                       target, current, abs(distance), tolerance, control)
            self._nav.vehicle.app('fd').r = control
            time.sleep(_NAV_SLEEP)
        raise CommandTimeout('rotate exceeded timeout')

    def clockwise(self, degrees, **kwargs):
        """Rotate clockwise by a number of degrees."""
        self(by=degrees, direction=Direction.CLOCKWISE, **kwargs)

    def counterclockwise(self, degrees, **kwargs):
        """Rotate counterclockwise by a number of degrees."""
        self(by=-degrees, direction=Direction.COUNTERCLOCKWISE, **kwargs)


class Goto(NavigationFactory):
    def __call__(self, waypoints, timeout=NotSet, tolerance=NotSet):
        """Move the vehicle to a waypoint or along a series of waypoints.

        Block until the vehicle is within tolerance of the final waypoint.
        """
        # NotSet resolution
        timeout = self.resolve(timeout, 'timeout')
        tolerance = self.resolve(tolerance, 'tolerance')

        # Sanity checks
        if not isinstance(tolerance, Real) or tolerance <= 0:
            raise ValueError('Tolerance must be set to a positive real number.')

        # Timeout
        # TODO Use vehicle time not local
        timeout = datetime.max if timeout is None else timeout + datetime.now()

        # Iterate through all given waypoints
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
                if datetime.now() > timeout:
                    raise CommandTimeout('goto exceeded timeout')
                distance = self._nav._geographic.distance(
                    cur, self._nav.position)
                if distance < tolerance:
                    self._nav.vehicle.info(
                        'goto expected %s actual %s (%s < %s m)',
                        cur, self._nav.position, distance, tolerance)
                    break
                time.sleep(_NAV_SLEEP)


class Vnav(NavigationFactory):
    def __call__(self, by=None, to=None, method=NotSet, timeout=NotSet,
                 tolerance=NotSet):
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
            timeout (Optional[Real]):
            tolerance (Real): The allowable error in altitude before the method
                sets the z-axis to 0 and returns.
        """
        # NotSet resolution
        method = self.resolve(method, 'method')
        timeout = self.resolve(timeout, 'timeout')
        tolerance = self.resolve(tolerance, 'tolerance')

        # Sanity checks
        if not by and not to:
            raise ValueError('Must set either by or to.')
        elif by and to:
            raise ValueError('Must not set both by and to.')
        if not method or not callable(method):
            raise ValueError('Must have a callable navigation method.')
        if not isinstance(tolerance, Real) or tolerance <= 0:
            raise ValueError('Tolerance must be set to a positive real number.')

        # Timeout
        # TODO Use vehicle time not local
        timeout = datetime.max if timeout is None else timeout + datetime.now()

        target_altitude = (self._nav.altitude + by) if by else to

        while datetime.now() < timeout:
            difference = abs(target_altitude - self._nav.altitude)
            if difference <= tolerance:
                self.info('vnav expected %s actual %s (%s < %s m)',
                          target_altitude, self._nav.altitude,
                          difference, tolerance)
                self._nav.vehicle.app('fd').z = 0.0
                return self
            control = method(self._nav.altitude, target_altitude)
            self.debug('vnav toward %.3f actual %.3f (%.3f < %.3f m) %.3f',
                       target_altitude, self._nav.altitude,
                       difference, tolerance, control)
            self._nav.vehicle.app('fd').z = control
            time.sleep(_NAV_SLEEP)
        raise CommandTimeout('vnav exceeded timeout')

    def down(self, distance, **kwargs):
        """Move down by a distance. See vnav for full documentation."""
        return self(by=-distance, **kwargs)

    def to(self, altitude, **kwargs):
        """Climb or descend to altitude. See vnav for full documentation."""
        return self(to=altitude, **kwargs)

    def up(self, distance, **kwargs):
        """Move up by a distance. See vnav for full documentation."""
        return self(by=distance, **kwargs)


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
