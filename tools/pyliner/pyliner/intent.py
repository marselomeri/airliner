"""
The intent module provides all the classes relevant to broadcasting Intents
across a Vehicle.
"""

from threading import Event

from pyliner.pyliner_error import PylinerError


class FutureTimeoutError(PylinerError):
    """Raised if an IntentFuture did not receive a reply within the
    specified timeout."""
    pass


class IntentNoReceiverError(PylinerError):
    """Raised if an Intent was not broadcast because no Apps indicated they were
     capable of receiving the specified action."""
    pass


class Intent(object):
    """An Intent is an abstraction of an operation to be performed.

    Intents are broadcast vehicle-wide or to single Apps to indicate that an
    action should be taken.

    See Also:
        https://developer.android.com/reference/android/content/Intent
    """
    def __init__(self, action, data=None, component=None):
        self.action = action
        self.component = component
        self.data = data

    def __repr__(self):
        s = '{}(action={!r}, data={!r}'.format(
            self.__class__.__name__, self.action, self.data, self.component)
        s += '' if not self.component else ' component=' + repr(self.component)
        s += ')'
        return s

    def is_explicit(self):
        return bool(self.component)


class IntentFilter(object):
    """Filters intents by matching actions from a list.

    Match using the contains `intent in IntentFilter()` syntax.

    If dynamic is callable and the intent does not match anything from actions,
    dynamic is called with the intent as an argument.
    """
    def __init__(self, actions=None, dynamic=None):
        self.actions = actions
        self.dynamic = dynamic

    def __str__(self):
        return '{}(actions={}'.format(self.__class__.__name__, self.actions) + \
               ', dynamic={}'.format(self.dynamic) if self.dynamic else '' + ')'

    def __contains__(self, intent):
        if not isinstance(intent, Intent):
            raise TypeError('IntentFilter can only contain Intents.')
        return intent.action in self.actions \
            or (self.dynamic(intent) if callable(self.dynamic) else False)


class IntentResponse(object):
    """Wrapper for the response from an Intent.

    Attributes:
        result: The returned value from code that processed an Intent.
        exception: The exception (if any) that was raised while processing an
            Intent.
    """
    def __init__(self, result=None, exception=None):
        self.result = result
        self.exception = exception

    def __repr__(self):
        return '{}(result={!r}, exception={!r})'.format(
            self.__class__.__name__, self.result, self.exception)


class IntentFuture(object):
    """Holds asynchronously-generated IntentResponses.

    When an Intent is broadcast the caller is given an IntentFuture which will
    be populated with IntentResponses as other Apps handle the broadcast Intent.
    """
    def __init__(self, caused_by):
        self.caused_by = caused_by
        self.complete = False
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
