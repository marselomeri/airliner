"""
The Geographic Sensor module provides a app that can be used to calculate
information about two Coordinates on Earth.

Sensors:
    GeographicSensor  Produces relevant world-based calculations.
"""

from copy import copy
from numbers import Real

from geographiclib.geodesic import Geodesic

from pyliner.action import ACTION_CALC_BEARING, ACTION_CALC_DISTANCE, ACTION_CALC_PBD
from pyliner.geographic import Geographic
from pyliner.navigation.position import Coordinate
from pyliner.app import App


class GeographicApp(Geographic, App):
    """A Sensor that produces relevant world-based calculations."""

    def __repr__(self):
        return 'GeographicSensor()'

    def __str__(self):
        return 'WGS84'

    def attach(self, vehicle_wrapper):
        super(GeographicApp, self).attach(vehicle_wrapper)
        self.vehicle.add_filter(
            lambda i: i.action == ACTION_CALC_BEARING,
            lambda i: GeographicApp.bearing(*i.data))
        self.vehicle.add_filter(
            lambda i: i.action == ACTION_CALC_DISTANCE,
            lambda i: GeographicApp.distance(*i.data))
        self.vehicle.add_filter(
            lambda i: i.action == ACTION_CALC_PBD,
            lambda i: GeographicApp.pbd(*i.data)
        )

    def detach(self):
        self.vehicle.clear_filter()
        super(GeographicApp, self).detach()

    @staticmethod
    def bearing(a, b):
        return GeographicApp._inverse(a, b)['azi1'] % 360

    @staticmethod
    def _direct(a, azim, dist):
        # type: (Coordinate, Real, Real) -> dict
        # Possibility of LRU cache here.
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Direct(a.latitude, a.longitude, azim, dist)

    @staticmethod
    def distance(a, b):
        return GeographicApp._inverse(a, b)['s12']

    @staticmethod
    def _inverse(a, b):
        # type: (Coordinate, Coordinate) -> dict
        # Possibility of LRU cache here.
        # noinspection PyUnresolvedReferences
        return Geodesic.WGS84.Inverse(a.latitude, a.longitude,
                                      b.latitude, b.longitude)

    @staticmethod
    def pbd(a, bearing, distance):
        direct = GeographicApp._direct(a, bearing, distance)
        b = copy(a)
        b.latitude = direct['lat2']
        b.longitude = direct['lon2']
        return b
