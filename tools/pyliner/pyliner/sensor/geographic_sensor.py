"""
The Geographic Sensor module provides a sensor that can be used to calculate
information about two Coordinates on Earth.

Sensors:
    GeographicSensor  Produces relevant world-based calculations.
"""

from copy import copy
from numbers import Real

from geographiclib.geodesic import Geodesic

from pyliner.geographic import Geographic
from pyliner.navigation.position import Coordinate
from pyliner.sensor import Sensor


class GeographicSensor(Geographic, Sensor):
    """A Sensor that produces relevant world-based calculations."""

    def __repr__(self):
        return 'Geographic()'

    def __str__(self):
        return 'WGS84'

    @staticmethod
    def bearing(a, b):
        return GeographicSensor._inverse(a, b)['azi1'] % 360

    @staticmethod
    def _direct(a, azim, dist):
        # type: (Coordinate, Real, Real) -> dict
        # Possibility of LRU cache here.
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Direct(a.latitude, a.longitude, azim, dist)

    @staticmethod
    def distance(a, b):
        return GeographicSensor._inverse(a, b)['s12']

    @staticmethod
    def _inverse(a, b):
        # type: (Coordinate, Coordinate) -> dict
        # Possibility of LRU cache here.
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Inverse(a.latitude, a.longitude,
                                      b.latitude, b.longitude)

    @staticmethod
    def pbd(a, bearing, distance):
        direct = GeographicSensor._direct(a, bearing, distance)
        b = copy(a)
        b.latitude = direct['lat2']
        b.longitude = direct['lon2']
        return b