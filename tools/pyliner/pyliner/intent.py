from threading import Event

from pyliner.pyliner_exceptions import PylinerError


class FutureTimeoutError(PylinerError):
    pass


class IntentNoReceiverError(PylinerError):
    pass


class Intent(object):
    def __init__(self, action, data=None, component=None):
        self.action = action
        self.component = component
        self.data = data

    # def __str__(self):
    #     return '{}(action={!r})'.format(self.__class__.__name__, self.action)

    def __repr__(self):
        s = '{}(action={!r}, data={!r}'.format(
            self.__class__.__name__, self.action, self.data, self.component)
        s += '' if not self.component else ' component=' + repr(self.component)
        s += ')'
        return s

    def is_explicit(self):
        return bool(self.component)


class IntentFilter(object):
    def __init__(self, actions=None, dynamic=None):
        self.actions = actions
        self.dynamic = dynamic

    def __contains__(self, intent):
        if not isinstance(intent, Intent):
            raise TypeError('IntentFilter can only contain Intents.')
        return intent.action in self.actions \
            or (self.dynamic(intent) if callable(self.dynamic) else False)


class IntentResponse(object):
    def __init__(self, result=None, exception=None):
        self.result = result
        self.exception = exception

    def __repr__(self):
        return '{}(result={}, exception={})'.format(
            self.__class__.__name__, self.result, self.exception)


class IntentFuture(object):
    def __init__(self, caused_by):
        self.caused_by = caused_by
        self.failure = None
        self.responses = []
        """:type: list[IntentResponse]"""

        self._add_callback = None
        self._event_first = Event()

    def add(self, response):
        self.responses.append(response)
        self._event_first.set()
        if callable(self._add_callback):
            self._add_callback(self)

    def add_callback(self, callback):
        self._add_callback = callback

    def first(self, timeout=None):
        self._event_first.wait(timeout=timeout)
        try:
            return self.responses[0]
        except IndexError:
            raise FutureTimeoutError()

    def recent(self, timeout=None):
        self._event_first.wait(timeout=timeout)
        try:
            return self.responses[-1]
        except IndexError:
            raise FutureTimeoutError()
