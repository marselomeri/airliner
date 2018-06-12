"""
The geographic module exposes a base class for a developer looking to implement
the required methods for their own Geographic calculations.

See Also:
    GeographicService
"""

from abc import abstractmethod, ABCMeta
from numbers import Real

from pyliner.navigation.position import Coordinate


class Geographic(object):
    """Interface to hold static methods for geographic calculations.

    An example implementation is provided as GeographicService.
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


