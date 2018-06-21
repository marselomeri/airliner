from unittest import TestCase

from pyliner.app import App
from pyliner.vehicle_access import VehicleAccess


class TestApp(TestCase):
    def test_lifecycle(self):
        s = App()
        self.assertEqual(App.DETACHED, s.state)
        self.assertIsNone(s.vehicle)
        # Attach
        s.attach(VehicleAccess('test'))
        self.assertEqual(App.ATTACHED, s.state)
        self.assertIsNotNone(s.vehicle)
        # Start
        s.start()
        self.assertEqual(App.STARTED, s.state)
        # Stop
        s.stop()
        self.assertEqual(App.ATTACHED, s.state)
        # Detach
        s.detach()
        self.assertEqual(App.DETACHED, s.state)
        self.assertIsNone(s.vehicle)
