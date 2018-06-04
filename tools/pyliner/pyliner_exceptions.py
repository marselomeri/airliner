class PylinerError(RuntimeError):
    pass


class InvalidCommandException(PylinerError):
    pass


class InvalidOperationException(PylinerError):
    pass


class UnauthorizedAtpError(PylinerError):
    pass


class InvalidStateError(ValueError):
    pass