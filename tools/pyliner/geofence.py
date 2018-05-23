from abc import abstractmethod
from enum import Enum

from sortedcontainers import SortedDict

from position import Position
from pyliner_module import PylinerModule


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
    """A simple box."""
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

    @property
    def bounding_box(self):
        return self


class LayerKind(Enum):
    ADDITIVE = 'ADDITIVE'
    SUBTRACTIVE = 'SUBTRACTIVE'


class _Layer(Volume):
    def __init__(self, name, kind):
        self.name = name
        self.kind = kind
        self.volumes = []
        """:type: list[Volume]"""

    def __contains__(self, item):
        return any(item in volume for volume in self.volumes) \
            if item in self.bounding_box else False

    @property
    def bounding_box(self):
        if not len(self.volumes):
            return None
        box = self.volumes[0].bounding_box
        for volume in self.volumes[1:]:
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

    def add_layer(self, layer_position, layer_name, layer_kind):
        if layer_position in self.layers:
            raise KeyError('This layer already exists.')
        self.layers[layer_position] = _Layer(name=layer_name, kind=layer_kind)

    def add_volume(self, layer, volume):
        self.layers[layer].volumes.append(volume)

    def remove_layer(self, position):
        del self.layers[position]

    @classmethod
    def required_telemetry_paths(cls):
        return None
