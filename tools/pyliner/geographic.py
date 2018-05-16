from abc import abstractmethod, ABCMeta
from collections import namedtuple

from geographiclib.geodesic import Geodesic


LatLon = namedtuple('LatLon', ['latitude', 'longitude'])


class Geographic(object):
    __metaclass__ = ABCMeta

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
    def place_bearing_distance(a, bearing, distance):
        """Calculate a new LatLon based on an initial position.

        Args:
            a (LatLon): Point A
            bearing (float): Direction in degrees [0, 360)
            distance (float): Distance in meters
        """
        raise NotImplementedError()


class GeographicWrapper(Geographic):
    @staticmethod
    def place_bearing_distance(a, bearing, distance):
        direct = GeographicWrapper._direct(a, bearing, distance)
        return LatLon(direct['lat2'], direct['lon2'])

    @staticmethod
    def _direct(a, azim, dist):
        # type: (LatLon, float, float) -> dict
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
