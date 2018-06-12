import math

from pyliner.navigation.position import Position


class Waypoint(Position):
    """4-dimensional coordinate, position + heading

    May be used as part of the arguments to a triplet command.
    """

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