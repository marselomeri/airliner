from threading import Event

from enum import Enum


INTENT_RESPONSE_SLEEP = 1.0 / 100.0


class EventType(Enum):
    """This goes with Event."""
    CONSOLE_OUT = 'CONSOLE_OUT'
    CONSOLE_IN = 'CONSOLE_IN'
    LOG = 'LOG'


class Intent(object):
    def __init__(self, origin, action, data=None, component=None):
        self.action = action
        self.component = component
        self.data = data
        self.origin = origin

    def __repr__(self):
        return '{}({!r}, {!r}, {!r})'.format(
            self.__class__.__name__, self.origin, self.action, self.component)

    def is_explicit(self):
        return bool(self.component)


class IntentResponse(object):
    def __init__(self, caused_by):
        self.caused_by = caused_by
        self.responses = []
        self._wait_first = Event()

    def add(self, response):
        self.responses.append(response)
        self._wait_first.set()

    def first(self, timeout=None):
        self._wait_first.wait(timeout=timeout)
        return self.responses[0]
