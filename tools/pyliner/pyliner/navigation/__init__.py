"""
The navigation package holds the builtin code for performing basic vehicle
navigation. Four types of navigation are provided by default, as well as a
Navigation app that users may attach to a vehicle.

Apps:
    Navigation  Takes control of the vehicle to perform movements.

Navigation Helpers:
    Goto  Move the vehicle to a waypoint or along a series of waypoints.
    Lnav  Perform a lateral movement.
    Rotate  Rotate the vehicle.
    Vnav  Perform a vertical movement.

The following modules are also available:
    control  Collection of useful navigation PID controllers.
    heading  Implementation of custom float that wraps [0-360).
    navigation_factory  Base class for navigation helpers.
    position  2D and 3D point classes.
    waypoint  Waypoint used in navigation.
"""

# TODO Find a place for this within Navigation or Vehicle
_NAV_SLEEP = 1.0 / 16.0
