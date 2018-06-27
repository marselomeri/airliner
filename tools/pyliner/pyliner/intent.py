from threading import Event


class Intent(object):
    def __init__(self, action, data=None, component=None):
        self.action = action
        self.component = component
        self.data = data

    def __repr__(self):
        s = '{}(action={!r}, data={!r}'.format(
            self.__class__.__name__, self.action, self.data, self.component)
        s += '' if not self.component else 'component=' + repr(self.component)
        s += ')'
        return s

    def is_explicit(self):
        return bool(self.component)


class IntentResponse(object):
    def __init__(self, result=None, exception=None):
        self.result = result
        self.exception = exception


class IntentFuture(object):
    def __init__(self, caused_by):
        self._add_callback = None
        self.caused_by = caused_by
        self._event_first = Event()
        self.responses = []
        """:type: list[IntentResponse]"""

    def add(self, response):
        self.responses.append(response)
        self._event_first.set()
        if callable(self._add_callback):
            self._add_callback(self)

    def add_callback(self, callback):
        self._add_callback = callback

    def first(self, timeout=None):
        self._event_first.wait(timeout=timeout)
        return self.responses[0]

    def first_result(self, timeout=None):
        return self.first(timeout=timeout).result

    def recent(self, timeout=None):
        self._event_first.wait(timeout=timeout)
        return self.responses[-1]

    def recent_result(self, timeout=None):
        return self.recent(timeout=timeout).result
