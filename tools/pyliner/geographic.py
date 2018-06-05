from abc import abstractmethod, ABCMeta
from copy import copy
from numbers import Real

from geographiclib.geodesic import Geodesic

from position import Coordinate
from sensor import Sensor


class GeographicBase(object):
    """Interface to hold static methods for geographic calculations.

    The user is free to implement their own methods, though an implementation
    is provided as Geographic.
    """
    __metaclass__ = ABCMeta

    @staticmethod
    @abstractmethod
    def bearing(a, b):
        # type: (Coordinate, Coordinate) -> Real
        """Calculate the bearing from a to b in degrees."""
        raise NotImplementedError()

    @staticmethod
    @abstractmethod
    def distance(a, b):
        # type: (Coordinate, Coordinate) -> Real
        """Calculate the distance between two points on the globe.

        Args:
            a (position.Coordinate): Point A
            b (position.Coordinate): Point B

        Returns:
            float: Distance in meters.
        """
        raise NotImplementedError()

    @staticmethod
    @abstractmethod
    def pbd(a, bearing, distance):
        # type: (Coordinate, Real, Real) -> Coordinate
        """Calculate a Place-Bearing-Distance (PBD) coordinate.

        Returns:
            (Coordinate): A copy of `a` with updated latitude and longitude.

        Args:
            a (position.Coordinate): Point A
            bearing (float): Direction in degrees [0, 360)
            distance (float): Distance in meters
        """
        raise NotImplementedError()


class Geographic(GeographicBase, Sensor):
    def __str__(self):
        return 'WGS84'

    @staticmethod
    def bearing(a, b):
        return Geographic._inverse(a, b)['azi1'] % 360

    @staticmethod
    def _direct(a, azim, dist):
        # type: (Coordinate, Real, Real) -> dict
        # Possibility of LRU cache here.
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Direct(a.latitude, a.longitude, azim, dist)

    @staticmethod
    def distance(a, b):
        return Geographic._inverse(a, b)['s12']

    @staticmethod
    def _inverse(a, b):
        # type: (Coordinate, Coordinate) -> dict
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
