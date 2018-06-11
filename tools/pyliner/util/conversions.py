"""
Provides shorthands for a handful of useful conversions.
"""
from datetime import timedelta


# Length
def feet(ft):
    """Convert from given feet to meters."""
    return ft * 0.3048


# Time
def hours(hrs):
    """Timedelta with hrs as hours."""
    return timedelta(hours=hrs)


def minutes(min):
    """Timedelta with min as minutes."""
    return timedelta(minutes=min)


def seconds(sec):
    """Timedelta with sec as seconds."""
    return timedelta(seconds=sec)
