import unittest

from geofence import Geofence, LayerKind, VerticalCylinder, Box
from geographic import Geographic
from position import Position, Coordinate


class TestGeofence(unittest.TestCase):
    def test_contains(self):
        geo = Geographic()
        fence = Geofence()
        base = fence.add_layer(0, 'base', LayerKind.ADDITIVE)
        tfr = fence.add_layer(1, 'tfr', LayerKind.SUBTRACTIVE)
        base.add_volume(Box(Position(1, 3, 0), Position(2, 5, 500)))
        tfr.add_volume(VerticalCylinder(geo, Coordinate(1.5, 4), 0, 3000, 1000))

        self.assertIn(Position(1.1, 3.2, 250), fence)
        self.assertNotIn(Position(1.5, 4.0, 100), fence)
        self.assertNotIn(Position(0, 0, 0), fence)
        self.assertNotIn(Position(1.1, 3.2, 550), fence)
