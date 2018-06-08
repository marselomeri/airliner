from collections import Container
from numbers import Real


class Heading(float):
    def __add__(self, other):
        if isinstance(other, Real):
            return Heading((float(self) + other) % 360)
        raise NotImplemented

    def __radd__(self, other):
        return self + other

    def __sub__(self, other):
        if isinstance(other, Real):
            return Heading((float(self) - other) % 360)
        raise NotImplemented

    def __rsub__(self, other):
        return self - other

    def range(self, low_range, high_range=None):
        return HeadingRange(
            self - low_range,
            self + (low_range if high_range is None else high_range))


class HeadingRange(Container):
    """Create a range of heading values, clockwise from min to max."""

    def __init__(self, min, max):
        self.min = min
        self.max = max

    def __contains__(self, x):
        wrap = self.min > self.max
        xgtmin = x >= self.min
        xltmax = x <= self.max
        return xgtmin or xltmax if wrap else xgtmin and xltmax

    def __repr__(self):
        return 'HeadingRange({}, {})'.format(self.min, self.max)
