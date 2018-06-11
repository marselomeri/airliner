from numbers import Real


class RealSuper(Real):
    """Default concrete implementation of Real.
    
    All methods call super if other is Real.
    """
    def __abs__(self):
        return super(RealSuper, self).__abs__()

    def __add__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__add__(other)
        raise NotImplemented

    def __radd__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__radd__(other)
        raise NotImplemented

    def __div__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__div__(other)
        raise NotImplemented

    def __rdiv__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__rdiv__(other)
        raise NotImplemented

    def __eq__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__eq__(other)
        raise NotImplemented

    def __float__(self):
        return super(RealSuper, self).__float__()

    def __floordiv__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__floordiv__(other)
        raise NotImplemented

    def __rfloordiv__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__rfloordiv__(other)
        raise NotImplemented

    def __le__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__le__(other)
        raise NotImplemented

    def __lt__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__lt__(other)
        raise NotImplemented

    def __mod__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__mod__(other)
        raise NotImplemented

    def __rmod__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__rmod__(other)
        raise NotImplemented

    def __mul__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__mul__(other)
        raise NotImplemented

    def __rmul__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__rmul__(other)
        raise NotImplemented

    def __neg__(self):
        return super(RealSuper, self).__neg__()

    def __pos__(self):
        return super(RealSuper, self).__pos__()

    def __pow__(self, exponent):
        if isinstance(exponent, Real):
            return super(RealSuper, self).__pow__(exponent)
        raise NotImplemented

    def __rpow__(self, base):
        if isinstance(base, Real):
            return super(RealSuper, self).__rpow__(base)
        raise NotImplemented

    def __truediv__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__truediv__(other)
        raise NotImplemented

    def __rtruediv__(self, other):
        if isinstance(other, Real):
            return super(RealSuper, self).__rtruediv__(other)
        raise NotImplemented

    def __trunc__(self):
        return super(RealSuper, self).__trunc__()
