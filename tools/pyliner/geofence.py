"""
Notes:
    This module is not set up to handle crossing anti-meridian.
    Currently you will get a large bounding box around the entire planet.
    TODO: How to identify bounding boxes that cross? Take smaller box?
"""

from abc import abstractmethod
from enum import Enum
from numbers import Real

from sortedcontainers import SortedDict

from geographic import GeographicBase
from position import Coordinate
from position import Position
from pyliner_module import PylinerModule
from util import indent


class Volume(object):
    @abstractmethod
    def __contains__(self, item):
        """True if the given item is contained within this Volume."""
        raise NotImplementedError

    @property
    @abstractmethod
    def bounding_box(self):
        # type: () -> Box
        """The min and max values for latitude, longitude, and altitude."""
        raise NotImplementedError


class Box(Volume):
    """A simple box. Aligned along latitude, longitude, and vertical."""
    def __init__(self, corner_1, corner_2):
        # type: (Position, Position) -> None
        self.min_latitude = min(corner_1.latitude, corner_2.latitude)
        self.max_latitude = max(corner_1.latitude, corner_2.latitude)
        self.min_longitude = min(corner_1.longitude, corner_2.longitude)
        self.max_longitude = max(corner_1.longitude, corner_2.longitude)
        self.min_altitude = min(corner_1.altitude, corner_2.altitude)
        self.max_altitude = max(corner_1.altitude, corner_2.altitude)

    def __contains__(self, item):
        return self.min_latitude <= item.latitude <= self.max_latitude \
            and self.min_longitude <= item.longitude <= self.max_longitude \
            and self.min_altitude <= item.altitude <= self.max_altitude

    def __or__(self, other):
        box = other.bounding_box
        return Box(Position(
            min(self.min_latitude, box.min_latitude),
            min(self.min_longitude, box.min_longitude),
            min(self.min_altitude, box.min_altitude)
        ), Position(
            max(self.max_latitude, box.max_latitude),
            max(self.max_longitude, box.max_longitude),
            max(self.max_altitude, box.max_altitude)
        ))

    def __str__(self):
        return 'Box(latitude=[{}, {}], longitude=[{}, {}], altitude=[{}, {}' \
               '])'.format(self.min_latitude, self.max_latitude,
                           self.min_longitude, self.max_longitude,
                           self.min_altitude, self.max_altitude)

    @property
    def bounding_box(self):
        return self


class VerticalCylinder(Volume):
    """A vertical right circular cylinder.

    Defined in a geographic system by a 2d coordinate, bounding altitudes and a
    radius in meters.
    """

    def __init__(self, geographic, center, low_altitude, high_altitude, radius):
        # type: (GeographicBase, Coordinate, Real, Real, Real) -> None
        self.geographic = geographic
        self.center = center
        self.high = high_altitude
        self.low = low_altitude
        self.radius = radius

    def __contains__(self, item):
        return self.low <= item.altitude <= self.high and \
               self.geographic.distance(self.center, item) <= self.radius

    def __str__(self):
        return 'VerticalCylinder(latitude={}, longitude={}, radius={}, low={}, ' \
               'high={})'.format(self.center.latitude, self.center.longitude,
                                 self.radius, self.low, self.high)

    @property
    def bounding_box(self):
        # Check for poles
        distance = self.geographic.distance
        pbd = self.geographic.pbd
        min_lat = max_lat = None
        if distance(self.center, Coordinate(90, 0)) <= self.radius:
            max_lat = 90
        if distance(self.center, Coordinate(-90, 0)) <= self.radius:
            min_lat = -90

        return Box(Position(
            min_lat or pbd(self.center, 180, self.radius).latitude,
            pbd(self.center, 270, self.radius).longitude,
            self.low
        ), Position(
            max_lat or pbd(self.center, 000, self.radius).latitude,
            pbd(self.center,  90, self.radius).longitude,
            self.high
        ))


class LayerKind(Enum):
    ADDITIVE = True
    SUBTRACTIVE = False


class _Layer(Volume):
    def __init__(self, name, kind):
        self.name = name
        self.kind = kind
        self._volumes = []
        """:type: list[Container]"""

    def __contains__(self, item):
        return any(item in volume for volume in self._volumes) \
            if item in self.bounding_box else False

    def __str__(self):
        return '{}\n'.format(self.name) + '\n'.join(
            '{}'.format(volume) for volume in indent(4, self._volumes))

    def add_volume(self, volume):
        self._volumes.append(volume)

    @property
    def bounding_box(self):
        if not len(self._volumes):
            return None
        box = self._volumes[0].bounding_box
        for volume in self._volumes[1:]:
            box |= volume
        return box


class Geofence(PylinerModule):
    """A Geofence defines the space a vehicle is allowed to operate within.

    A geofence is constructed by layering additive and subtractive geometry
    to construct a 3-dimensional space of operations that a drone is allowed to
    fly in.

    Within a layer, a point is determined to be inside as if all the volumes in
    that layer were taken as a union.
    """

    def __init__(self):
        super(Geofence, self).__init__()
        self.layers = SortedDict()
        """:type: dict[Any, Layer]"""

    def __contains__(self, item):
        """True if the given item is contained within the Geofence."""
        contained = False
        for layer in self.layers.values():
            if item in layer:
                contained = layer.kind is LayerKind.ADDITIVE
        return contained

    def __str__(self):
        return 'Geofence{\n' + '\n'.join(' {}{}: {}'.format(
                '+' if layer.kind is LayerKind.ADDITIVE else '-',
                order, layer) for order, layer in self.layers.items()) + '\n}'

    def add_layer(self, layer_position, layer_name, layer_kind):
        if layer_position in self.layers:
            raise KeyError('This layer already exists.')
        layer = _Layer(name=layer_name, kind=layer_kind)
        self.layers[layer_position] = layer
        return layer

    def remove_layer(self, position):
        del self.layers[position]

    @classmethod
    def required_telemetry_paths(cls):
        return None
