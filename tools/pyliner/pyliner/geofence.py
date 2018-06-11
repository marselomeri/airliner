"""
Notes:
    This module is not set up to handle crossing anti-meridian.
    Currently you will get a large bounding box around the entire planet.
    TODO: How to identify bounding boxes that cross? Take smaller box?
"""
import warnings
from abc import abstractmethod, ABCMeta
from collections import Container
from functools import partial
from numbers import Real

from enum import Enum
from future.moves import itertools
from sortedcontainers import SortedDict

from app import App
from geographic import GeographicBase
from position import Coordinate
from position import Position
from telemetry import ManualSetpoint
from util import indent, PeriodicExecutor


class FenceGenerator(object):
    def __init__(self, geographic, *classes):
        self.geographic = geographic
        self.curry(*classes)

    def curry(self, *classes):
        for c in classes:
            if not issubclass(c, Volume):
                warnings.warn('Curry was expecting a subclass of Volume and '
                              'received a {}'.format(c))
            setattr(self, c.__name__, partial(c, geographic=self.geographic))


class Volume(Container):
    """A generic volume class. Extend to create concrete volumes.

    By default, `c = a | b` will return a new CompositeVolume made of a and b.
    """
    __metaclass__ = ABCMeta

    def __init__(self, geographic):
        self.geographic = geographic

    def __or__(self, other):
        return CompositeVolume(self.geographic, {self, other})

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
        super(Box, self).__init__(None)
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

    def __str__(self):
        return 'Box(latitude=[{}, {}], longitude=[{}, {}], altitude=[{}, {}' \
               '])'.format(self.min_latitude, self.max_latitude,
                           self.min_longitude, self.max_longitude,
                           self.min_altitude, self.max_altitude)

    @property
    def bounding_box(self):
        return self


class CompositeVolume(Volume, set):
    """A volume directly composed of the union of multiple other volumes."""

    def __init__(self, geographic, volumes=None):
        Volume.__init__(self, geographic)
        set.__init__(self)
        if volumes:
            self.update(volumes)

    def __contains__(self, x):
        """Test whether a volume or a point are contained in this volume.

        If x is a Volume, test if the volume is a member of this
        CompositeVolume. If x is anything else, test if x is contained in any of
        the volumes that make up this CompositeVolume.

        Notes:
            Does not test if an arbitrary volume is entirely contained within
            this CompositeVolume.
        """
        return any(x in volume for volume in self) \
            if not isinstance(x, Volume) \
            else super(CompositeVolume, self).__contains__(x)

    def add(self, volume):
        self._check_geographic(volume)
        super(CompositeVolume, self).add(volume)

    @property
    def bounding_box(self):
        boxes = filter(lambda bb: bb is not None,
                       (x.bounding_box for x in self))
        if not boxes:
            return None
        return Box(
            Position(
                min(x.min_latitude for x in boxes),
                min(x.min_longitude for x in boxes),
                min(x.min_altitude for x in boxes)
            ), Position(
                max(x.max_latitude for x in boxes),
                max(x.max_longitude for x in boxes),
                max(x.max_altitude for x in boxes)
            )
        )

    def _check_geographic(self, other):
        if self.geographic and other.geographic \
                and other.geographic is not self.geographic:
            warnings.warn('Volume geographics do not match.')

    def flatten(self):
        """Return a flattened CompositeVolume."""
        todo = list(self)
        flat = set()
        for volume in todo:
            if isinstance(volume, CompositeVolume):
                todo.extend(volume)
            else:
                flat.add(volume)
        return CompositeVolume(self.geographic, flat)

    def update(self, *s):
        for volume in itertools.chain(s):
            self._check_geographic(volume)
        super(CompositeVolume, self).update(*s)


class LayerCake(CompositeVolume):
    """Define a layer-cake volume.

    Airspace around major airports is often described as an "upside-down layered
    cake", with larger rings at higher altitudes. Each ring is additive to the
    whole volume, and rings may intersect in altitude.
    """

    def __init__(self, geographic, center, rings=None):
        super(LayerCake, self).__init__(geographic, rings)
        self.center = center

    def add_ring(self, radius, low, high):
        self.add(
            VerticalCylinder(self.geographic, self.center, low, high, radius))


class VerticalCylinder(Volume):
    """A vertical right circular cylinder.

    Defined in a geographic system by a 2d coordinate, bounding altitudes and a
    radius in meters.
    """

    def __init__(self, geographic, center, radius, low, high):
        # type: (GeographicBase, Coordinate, Real, Real, Real) -> None
        super(VerticalCylinder, self).__init__(geographic)
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

        # If the cylinder intersects a pole the latitude caps and the longitude
        # is the full range.
        min_lat = max_lat = min_lon = max_lon = None
        if distance(self.center, Coordinate(90, 0)) <= self.radius:
            max_lat = 90
        if distance(self.center, Coordinate(-90, 0)) <= self.radius:
            min_lat = -90
        if max_lat or min_lat:
            min_lon = 0
            max_lon = 360

        return Box(Position(
            min_lat or pbd(self.center, 180, self.radius).latitude,
            min_lon or pbd(self.center, 270, self.radius).longitude,
            self.low
        ), Position(
            max_lat or pbd(self.center, 000, self.radius).latitude,
            max_lon or pbd(self.center, 90, self.radius).longitude,
            self.high
        ))


class LayerKind(Enum):
    ADDITIVE = True
    SUBTRACTIVE = False


class Layer(CompositeVolume):
    def __init__(self, name, kind, geographic=None):
        super(Layer, self).__init__(geographic)
        self.name = name
        self.kind = kind

    def __contains__(self, other):
        return other in self.bounding_box \
               and super(Layer, self).__contains__(other)

    def __str__(self):
        return '{}\n'.format(self.name) + '\n'.join(
            '{}'.format(volume) for volume in indent(4, self))


class Geofence(App):
    """A Geofence defines the space a vehicle is allowed to operate within.

    A geofence is constructed by layering additive and subtractive geometry
    to construct a 3-dimensional space of operations that a drone is allowed to
    fly in.

    Within a layer, a point is determined to be inside as if all the volumes in
    that layer were taken as a union.
    """
    # TODO Use a small memory database (like TinyDB) to handle layer mapping.
    #   Added benefit of allowing both name and order mapping to layer at once.

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
        self.gen = None
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
        if not isinstance(layer_kind, LayerKind):
            raise TypeError('layer_kind must be of type LayerKind.')
        layer = Layer(name=layer_name, kind=layer_kind)
        self.layers[layer_position] = layer
        return layer

    def attach(self, vehicle):
        super(Geofence, self).attach(vehicle)
        self._check_thread = PeriodicExecutor(
            self._check_fence, every=1,
            logger=self.vehicle.logger, name='FenceCheck',
            exception=lambda e: self.vehicle.exception('Geofence Exception'))
        self._check_thread.start()
        geographic = self.vehicle.sensor('geographic')
        self.gen = FenceGenerator(geographic,
                                  Box, LayerCake, VerticalCylinder)

    def _check_fence(self):
        old = self.fence_violation
        self.fence_violation = self.fence_violation or \
                               (self.enabled and self.position not in self)
        if not old and self.fence_violation:
            self.vehicle.error('Encountered Fence Violation at %s',
                               self.position)
            print('Encountered fence violation. Press Ctrl-C twice to exit.')

    def detach(self):
        super(Geofence, self).detach()
        self._check_thread.stop()
        self.gen = None

    def layer_by_name(self, name):
        for layer in self.layers.values():
            if layer.name == name:
                return layer

    @property
    def position(self):
        return Position(
            App._telem(self.req_telem['latitude'])(self),
            App._telem(self.req_telem['longitude'])(self),
            App._telem(self.req_telem['altitude'])(self)
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
