import unittest

from pyliner.service import Service
from pyliner.vehicle_access import VehicleAccess


class TestService(unittest.TestCase):
    def test_lifecycle(self):
        s = Service()
        self.assertEqual(Service.DETACHED, s.state)
        self.assertIsNone(s.vehicle)
        # Attach
        s.attach(VehicleAccess('test'))
        self.assertEqual(Service.ATTACHED, s.state)
        self.assertIsNotNone(s.vehicle)
        # Start
        s.start()
        self.assertEqual(Service.STARTED, s.state)
        # Stop
        s.stop()
        self.assertEqual(Service.ATTACHED, s.state)
        # Detach
        s.detach()
        self.assertEqual(Service.DETACHED, s.state)
        self.assertIsNone(s.vehicle)
