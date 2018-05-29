"""
Notes:
    This module is not set up to handle crossing anti-meridian.
    Currently you will get a large bounding box around the entire planet.
    TODO: How to identify bounding boxes that cross? Take smaller box?
"""

from abc import abstractmethod
from collections import Container
from enum import Enum
from numbers import Real

from sortedcontainers import SortedDict

from geographic import GeographicBase
from position import Coordinate
from position import Position
from pyliner_module import PylinerModule
from telemetry import ManualSetpoint
from util import indent, PeriodicExecutor


class FenceGenerator(object):
    def __init__(self, geographic):
        self.geographic = geographic


class Volume(Container):
    @property
    @abstractmethod
    def bounding_box(self):
        # type: () -> Box
        """The min and max values for latitude, longitude, and altitude."""
        raise NotImplementedError


class Arc(Volume):
    def __init__(self, geographic, ):
        pass

    def __contains__(self, x):
        pass

    @property
    def bounding_box(self):
        pass


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

    def __contains__(self, other):
        return self.min_latitude <= other.latitude <= self.max_latitude \
               and self.min_longitude <= other.longitude <= self.max_longitude \
               and self.min_altitude <= other.altitude <= self.max_altitude

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


class LayerCake(Volume):
    """Define a layer-cake volume.

    Airspace around major airports is often described as an "upside-down layered
    cake", with larger rings at higher altitudes. Each ring is additive to the
    whole volume, and rings may intersect in altitude.
    """
    def __init__(self, geographic, center):
        self.geographic = geographic
        self.center = center
        self.rings = []

    def __contains__(self, x):
        return any(x in ring for ring in self.rings)

    def add_ring(self, radius, low, high):
        self.rings.append(VerticalCylinder(self.geographic, self.center,
                                           low, high, radius))

    @property
    def bounding_box(self):
        return reduce(lambda x, y: x.bounding_box | y.bounding_box,
                      self.rings, NullBox())


class NullBox(Box):
    """A box with no size nor position. Can be safely OR'd with other volumes.

    OR'ing a NullBox with any other volume will return the bounding box of the
    other volume.

    A null box does not define any any attributes on purpose. It is meant as a
    base condition for loops which take unions of volumes without needing an
    explicit initial volume.

    bounding_box and __contains__ raise AttributeError instead of returning a
    default value to indicate that the user is meant to take the union of this
    volume and something else first before performing other operations.
    """
    def __init__(self):
        super(NullBox, self).__init__(
            Position(None, None, None), Position(None, None, None))

    def __contains__(self, other):
        raise AttributeError('NullBox does not contain anything.')

    def __or__(self, other):
        return other.bounding_box

    @property
    def bounding_box(self):
        raise AttributeError('NullBox does not define a bounding box.')


class VerticalCylinder(Volume):
    """A vertical right circular cylinder.

    Defined in a geographic system by a 2d coordinate, bounding altitudes and a
    radius in meters.
    """

    def __init__(self, geographic, center, radius, low, high):
        # type: (GeographicBase, Coordinate, Real, Real, Real) -> None
        self.geographic = geographic
        self.center = center
        self.high = high
        self.low = low
        self.radius = radius

    def __contains__(self, other):
        return self.low <= other.altitude <= self.high and \
               self.geographic.distance(self.center, other) <= self.radius

    def __repr__(self):
        return 'VerticalCylinder({}, {}, {}, {}, {})'.format(
            self.geographic, self.center, self.radius, self.low, self.high)

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
        """:type: list[Volume]"""

    def __contains__(self, other):
        return any(other in volume for volume in self._volumes) \
            if other in self.bounding_box else False

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

    req_telem = {
        'latitude': '/Airliner/CNTL/VehicleGlobalPosition/Lat',
        'longitude': '/Airliner/CNTL/VehicleGlobalPosition/Lon',
        'altitude': '/Airliner/CNTL/VehicleGlobalPosition/Alt'
    }

    def __init__(self):
        super(Geofence, self).__init__()
        self._check_thread = None
        self.enabled = False
        self.fence_violation = False
        self.layers = SortedDict()
        """:type: dict[Any, _Layer]"""

    def __contains__(self, other):
        """True if the given other is contained within the Geofence."""
        contained = False
        for layer in self.layers.values():
            if other in layer:
                contained = layer.kind is LayerKind.ADDITIVE
        return contained

    def __str__(self):
        return 'Geofence{\n' + '\n'.join(' {}{}: {}'.format(
                '+' if layer.kind is LayerKind.ADDITIVE else '-',
                order, layer) for order, layer in self.layers.items()) + '\n}'

    def add_layer(self, layer_position, layer_name, layer_kind):
        if layer_position in self.layers:
            raise KeyError('This layer already exists.')
        # if not isinstance(layer_kind, LayerKind): # TODO make this work with Enum
        #     raise TypeError('layer_kind must be of type LayerKind.')
        layer = _Layer(name=layer_name, kind=layer_kind)
        self.layers[layer_position] = layer
        return layer

    def attach(self, vehicle):
        super(Geofence, self).attach(vehicle)
        self._check_thread = PeriodicExecutor(self._check_fence)
        self._check_thread.start()

    def _check_fence(self):
        old = self.fence_violation
        self.fence_violation = self.fence_violation or \
                               (self.enabled and self.position not in self)
        if not old and self.fence_violation:
            print('Fence Violation')

    def detach(self):
        super(Geofence, self).detach()
        self._check_thread.stop()

    def layer_by_name(self, name):
        for layer in self.layers.values():
            if layer.name == name:
                return layer

    @property
    def position(self):
        return Position(
            PylinerModule._telem(self.req_telem['latitude'])(self),
            PylinerModule._telem(self.req_telem['longitude'])(self),
            PylinerModule._telem(self.req_telem['altitude'])(self)
        )

    def remove_layer(self, position):
        del self.layers[position]

    @classmethod
    def required_telemetry_paths(cls):
        return cls.req_telem.values()

    @property
    def telemetry(self):
        if self.fence_violation:
            return ManualSetpoint(ReturnSwitch=1, GearSwitch=3, ArmSwitch=1)
        return None

    @property
    def telemetry_available(self):
        return self.fence_violation
