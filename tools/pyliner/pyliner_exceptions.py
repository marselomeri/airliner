class PylinerError(RuntimeError):
    pass


class BlockedIoError(PylinerError):
    pass


class CommandTimeout(PylinerError):
    pass


class InvalidCommandException(PylinerError):
    pass


class InvalidOperationException(PylinerError):
    pass


class InvalidStateError(PylinerError, ValueError):
    pass


class UnauthorizedAtpError(PylinerError):
    pass
