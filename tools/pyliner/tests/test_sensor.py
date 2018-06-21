import unittest

from pyliner.sensor import Sensor
from pyliner.vehicle_access import VehicleAccess


class TestSensor(unittest.TestCase):
    def test_lifecycle(self):
        s = Sensor()
        self.assertEqual(Sensor.DETACHED, s.state)
        self.assertIsNone(s.vehicle)
        # Attach
        s.attach(VehicleAccess('test'))
        self.assertEqual(Sensor.ATTACHED, s.state)
        self.assertIsNotNone(s.vehicle)
        # Detach
        s.detach()
        self.assertEqual(Sensor.DETACHED, s.state)
        self.assertIsNone(s.vehicle)
