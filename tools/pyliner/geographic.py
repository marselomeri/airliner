import math
from abc import abstractmethod, ABCMeta
from copy import copy
from numbers import Real

from geographiclib.geodesic import Geodesic

__all__ = ['Geographic', 'LatLon', 'Waypoint']


class LatLon(object):
    def __init__(self, latitude, longitude):
        self.latitude = latitude
        self.longitude = longitude

    def __repr__(self):
        return '{}({}, {})'.format(self.__class__.__name__,
                                   self.latitude, self.longitude)


class Waypoint(LatLon):
    def __init__(self, latitude, longitude, altitude=None, heading=None):
        super(Waypoint, self).__init__(latitude, longitude)
        self.altitude = altitude
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


class GeographicBase(object):
    """Interface to hold static methods for geographic calculations.

    The user is free to implement their own methods, though an implementation
    is provided as Geographic.
    """
    __metaclass__ = ABCMeta

    @staticmethod
    @abstractmethod
    def bearing(a, b):
        # type: (LatLon, LatLon) -> float
        """Calculate the bearing from a to b in degrees."""
        raise NotImplementedError()

    @staticmethod
    @abstractmethod
    def distance(a, b):
        # type: (LatLon, LatLon) -> float
        """Calculate the distance between two points on the globe.

        Args:
            a (LatLon): Point A
            b (LatLon): Point B

        Returns:
            float: Distance in meters.
        """
        raise NotImplementedError()

    @staticmethod
    @abstractmethod
    def pbd(a, bearing, distance):
        # type: (LatLon, Real, Real) -> LatLon
        """Calculate a Place-Bearing-Distance (PBD) coordinate.

        Returns:
            (LatLon): A copy of `a` with updated latitude and longitude.

        Args:
            a (LatLon): Point A
            bearing (float): Direction in degrees [0, 360)
            distance (float): Distance in meters
        """
        raise NotImplementedError()


class Geographic(GeographicBase):
    @staticmethod
    def bearing(a, b):
        return Geographic._inverse(a, b)['azi1'] % 360

    @staticmethod
    def _direct(a, azim, dist):
        # type: (LatLon, Real, Real) -> dict
        # Possibility of LRU cache here.
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Direct(a.latitude, a.longitude, azim, dist)

    @staticmethod
    def distance(a, b):
        return Geographic._inverse(a, b)['s12']

    @staticmethod
    def _inverse(a, b):
        # type: (LatLon, LatLon) -> dict
        # Possibility of LRU cache here.
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Inverse(a.latitude, a.longitude,
                                      b.latitude, b.longitude)

    @staticmethod
    def pbd(a, bearing, distance):
        direct = Geographic._direct(a, bearing, distance)
        b = copy(a)
        b.latitude = direct['lat2']
        b.longitude = direct['lon2']
        return b
