"""
The geofence package provides sample volumes and a Geofence application.

Apps:
    Geofence  Maintains a volumetric space of operations for the vehicle and
        commands an RTL in the event of a violation.

Volumes:
    Layer  Primarily used by the geofence, layers of volumes.
    LayerCake  A set of cylinders around a single Coordinate.

Modules:
    volume  Collection of base and simple Volume classes.

Notes:
    This package is not set up to handle crossing the anti-meridian.
    Currently you will get a large bounding box around the entire planet.
    TODO: How to identify bounding boxes that cross? Take smaller box?
"""
import warnings
from functools import partial

from enum import Enum
from sortedcontainers import SortedDict

from pyliner.app import App
from pyliner.geofence.volume import Volume, CompositeVolume, Box, \
    VerticalCylinder
from pyliner.navigation.position import Position
from pyliner.telemetry import ManualSetpoint
from pyliner.util import indent, PeriodicExecutor


class FenceGenerator(object):
    """Curry a bunch of Volumes with the same Geographic."""

    def __init__(self, geographic, *classes):
        self.geographic = geographic
        self.curry(*classes)

    def curry(self, *classes):
        for c in classes:
            if not issubclass(c, Volume):
                warnings.warn('Curry was expecting a subclass of Volume and '
                              'received a {}'.format(c))
            setattr(self, c.__name__, partial(c, geographic=self.geographic))


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


class LayerKind(Enum):
    """Whether a layer is additive or subtractive."""
    ADDITIVE = True
    SUBTRACTIVE = False


class Layer(CompositeVolume):
    """A layer of volumes in a geofence."""
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
