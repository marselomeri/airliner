"""
Container module for the basic 2 and 3-dimensional coordinate classes.

Airspace is inherently 3-dimensional, favor the Position class over Coordinate
whenever feasible.
"""


class Coordinate(object):
    """A 2-dimensional point on the Earth.

    Represented by latitude and longitude in degrees.
    """
    def __init__(self, latitude, longitude):
        self.latitude = latitude
        self.longitude = longitude

    def __repr__(self):
        return '{}({}, {})'.format(self.__class__.__name__,
                                   self.latitude, self.longitude)


class Position(Coordinate):
    """A 3-dimensional point above the Earth.

    Represented by latitude and longitude in degrees, and altitude in meters.
    """
    def __init__(self, latitude, longitude, altitude):
        super(Position, self).__init__(latitude, longitude)
        self.altitude = altitude
