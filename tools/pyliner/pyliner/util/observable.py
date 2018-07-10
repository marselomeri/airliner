class Observable(object):
    def __init__(self):
        self.observers = []

    def register(self, observer):
        if not callable(observer):
            raise TypeError('Observer must be callable.')
        self.observers.append(observer)

    def notify(self):
        for observer in self.observers:
            observer(self)
