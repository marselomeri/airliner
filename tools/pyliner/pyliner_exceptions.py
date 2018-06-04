class PylinerError(RuntimeError):
    pass


class BlockedIoError(PylinerError):
    pass


class InvalidCommandException(PylinerError):
    pass


class InvalidOperationException(PylinerError):
    pass


class InvalidStateError(ValueError):
    pass


class UnauthorizedAtpError(PylinerError):
    pass
