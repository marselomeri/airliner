from abc import abstractmethod, ABCMeta
from collections import namedtuple
from numbers import Number, Real

from geographiclib.geodesic import Geodesic


LatLon = namedtuple('LatLon', ['latitude', 'longitude'])


class Geographic(object):
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

        Args:
            a (LatLon): Point A
            bearing (float): Direction in degrees [0, 360)
            distance (float): Distance in meters
        """
        raise NotImplementedError()


class GeographicWrapper(Geographic):
    @staticmethod
    def bearing(a, b):
        return GeographicWrapper._inverse(a, b)['azi1'] % 360

    @staticmethod
    def _direct(a, azim, dist):
        # type: (LatLon, Real, Real) -> dict
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Direct(a.latitude, a.longitude, azim, dist)

    @staticmethod
    def distance(a, b):
        return GeographicWrapper._inverse(a, b)['s12']

    @staticmethod
    def _inverse(a, b):
        # type: (LatLon, LatLon) -> dict
        # Possibility of LRU cache here.
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Inverse(a.latitude, a.longitude,
                                      b.latitude, b.longitude)

    @staticmethod
    def pbd(a, bearing, distance):
        direct = GeographicWrapper._direct(a, bearing, distance)
        return LatLon(direct['lat2'], direct['lon2'])
