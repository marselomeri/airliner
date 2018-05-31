import unittest

from geofence import Geofence, LayerKind, VerticalCylinder, Box
from geographic import Geographic
from position import Position, Coordinate


class TestGeofence(unittest.TestCase):
    def setUp(self):
        self.geo = Geographic()
        self.fence = Geofence()

    def test_box(self):
        box = Box(Position(0, 0, 0), Position(2, 2, 2))

        self.assertIn(Position(1, 1, 1), box)
        self.assertIn(Position(0, 0, 0), box)
        self.assertIn(Position(1, 1, 2), box)
        self.assertNotIn(Position(2.1, 1, 1), box)

    def test_composite(self):
        box1 = Box(Position(0, 0, 0), Position(2, 2, 2))
        box2 = Box(Position(4, 4, 4), Position(6, 6, 6))

        union = box1 | box2

        self.assertIn(Position(1, 1, 1), union)
        self.assertIn(Position(5, 5, 5), union)
        self.assertNotIn(Position(3, 3, 3), union)
        self.assertIn(Position(3, 3, 3), union.bounding_box)

    def test_cylinder(self):
        # TODO Make this
        raise NotImplementedError

    def test_fence(self):
        geo = Geographic()
        fence = Geofence()

        base = fence.add_layer(0, 'base', LayerKind.ADDITIVE)
        base.add(Box(Position(1, 3, 0), Position(3, 5, 1000)))

        tfr = fence.add_layer(1, 'tfr', LayerKind.SUBTRACTIVE)
        tfr.add(VerticalCylinder(geo, Coordinate(2, 4), 500, 0, 1000))

        self.assertIn(Position(1.1, 3.2, 250), fence)
        self.assertNotIn(Position(2, 4, 100), fence)
        self.assertNotIn(Position(0, 0, 0), fence)
        self.assertNotIn(Position(1.1, 3.2, 11000), fence)
