import time
from collections import Iterable
from datetime import datetime
from numbers import Real

from pyliner.navigation import _NAV_SLEEP
from pyliner.navigation.navigation_factory import NavigationFactory, NotSet
from pyliner.pyliner_exceptions import CommandTimeout
from pyliner.telemetry import SetpointTriplet
from pyliner.util import shifter


class Goto(NavigationFactory):
    """Move the vehicle to a waypoint or along a series of waypoints."""

    def __call__(self, waypoints, tolerance=NotSet, timeout=NotSet):
        """Block until the vehicle is within tolerance of the final waypoint.

        Args:
            waypoints: A single waypoint or an iterable of waypoints for the
                vehicle to follow.
            tolerance (Real): The allowable error in altitude before the method
                sets the z-axis to 0 and returns.
            timeout (Optional[timedelta]): If not None, the amount of time the
                method has to complete an operation before raising
                CommandTimeout. If None the timeout is datetime.max.
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
