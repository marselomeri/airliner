class PylinerError(RuntimeError):
    pass


class InvalidCommandException(PylinerError):
    pass


class InvalidOperationException(PylinerError):
    pass
