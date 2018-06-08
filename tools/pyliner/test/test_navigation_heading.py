import unittest

from navigation.heading import Heading, HeadingRange


class TestHeading(unittest.TestCase):
    def test_add_integer(self):
        a = Heading(0)
        a += 30
        a = a + 30
        a = 30 + a
        self.assertEqual(a, 90, 'Did not add integer.')
        self.assertIsInstance(a, Heading, 'Did not retain Heading type.')

    def test_sub_integer(self):
        a = Heading(90)
        a -= 45
        a = a - 45
        self.assertEqual(a, 0, 'Did not subtract integer.')
        self.assertIsInstance(a, Heading, 'Did not retain Heading type.')

    def test_overflow(self):
        a = Heading(350)
        a += 20
        self.assertEqual(a, 10, 'Did not overflow 360.')

    def test_underflow(self):
        a = Heading(10)
        a -= 20
        self.assertEqual(a, 350, 'Did not underflow 360.')

    def test_range(self):
        a = Heading(20)
        r = a.range(45)

        self.assertIn(335, r, 'Lower bound not inside range.')
        self.assertIn(65, r, 'Upper bound not inside range.')
        self.assertIn(0, r, 'North not in range.')
        self.assertNotIn(330, r, 'Out of range.')
        self.assertNotIn(70, r, 'Out of range.')


class TestHeadingRange(unittest.TestCase):
    def test_normal(self):
        low, mid, high, not1 = 20, 30, 40, 50
        a = HeadingRange(low, high)
        self.assertIn(low, a, 'Lower bound not inside range.')
        self.assertIn(mid, a, 'Middle value not inside range.')
        self.assertIn(high, a, 'Upper bound not inside range.')

        self.assertNotIn(not1, a, 'Out of range.')

    def test_wrap(self):
        low, mid, high, not1, not2 = 350, 0, 10, 20, 340
        a = HeadingRange(low, high)
        self.assertIn(low, a, 'Lower bound not inside range.')
        self.assertIn(mid, a, 'Middle value not inside range.')
        self.assertIn(high, a, 'Upper bound not inside range.')

        self.assertNotIn(not1, a, 'Out of range.')
        self.assertNotIn(not2, a, 'Out of range.')
