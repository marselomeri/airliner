class MutableVal(object):
    def __init__(self, val=None):
        self._val = val

    @property
    def val(self):
        return self._val

    @val.setter
    def val(self, val):
        self._val = val
