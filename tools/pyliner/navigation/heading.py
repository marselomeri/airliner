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
