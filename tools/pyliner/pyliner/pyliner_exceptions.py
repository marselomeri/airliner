"""
This module provides all of the Pyliner exceptions that may be encountered
during runtime. All of them are subclasses of the base PylinerError.
"""


class PylinerError(RuntimeError):
    """Base PylinerError"""
    pass


class BlockedIoError(PylinerError):
    pass


class CommandTimeout(PylinerError):
    """Raised if a command times out."""
    pass


class InvalidCommandException(PylinerError):
    """Raised if a command does not exist."""
    pass


class InvalidOperationException(PylinerError):
    """Raised if an operation is invalid."""
    pass


class InvalidStateError(PylinerError, ValueError):
    """Raised if continuing would perform an illegal state transition."""
    pass


class UnauthorizedAtpError(PylinerError):
    """Raised if the user denies ATP."""
    pass
