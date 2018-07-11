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
    """
    def __init__(self, actions=None):
        self.actions = actions
        self.dynamic = None

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

    If the handling App processed the Intent properly, result will hold the
    returned value. If the handling App raised an exception during execution
    then exception will hold the exception that was raised.

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
    """Hold asynchronously-generated IntentResponses.

    When an Intent is broadcast the caller is given an IntentFuture which will
    be populated with IntentResponses as other Apps handle the Intent.
    """
    def __init__(self, caused_by):
        self.caused_by = caused_by
        self.failure = None
        self.responses = []
        """:type: list[IntentResponse]"""

        self._add_callback = None
        self._complete = Event()
        self._event_first = Event()

    def add(self, response):
        """Add a response to this Future. Call callback if set."""
        self.responses.append(response)
        self._event_first.set()
        if self._add_callback is not None:
            self._add_callback(self)

    def add_callback(self, callback):
        """Add a callback to be called whenever a new response is received."""
        if callable(self._add_callback):
            self._add_callback = callback
        else:
            raise TypeError('callback must be callable.')

    @property
    def complete(self):
        return self._complete.is_set()

    @complete.setter
    def complete(self, value):
        if value is True:
            self._complete.set()
        else:
            raise ValueError('IntentFuture.complete can only be set to True.')

    def first(self, timeout=None):
        """Return the first response received.

        Raises:
            FutureTimeoutError: If no responses were received by the end
                of the timeout.
        """
        self._event_first.wait(timeout=timeout)
        try:
            return self.responses[0]
        except IndexError:
            raise FutureTimeoutError()

    def recent(self, timeout=None):
        """Return the most recent response received.

        Raises:
            FutureTimeoutError: If no responses were received by the end
                of the timeout.
        """
        self._event_first.wait(timeout=timeout)
        try:
            return self.responses[-1]
        except IndexError:
            raise FutureTimeoutError()

    def wait(self, timeout=None):
        self._complete.wait(timeout)
