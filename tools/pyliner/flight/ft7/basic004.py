"""
Rotate the vehicle

Requirements Fulfilled:
    PYLINER001
    PYLINER003
    PYLINER004
    PYLINER010
    PYLINER011
    PYLINER012
    PYLINER013
    PYLINER014
    PYLINER016
"""

from os.path import join, dirname, abspath, basename

import time

import pyliner
from pyliner import FlightMode
from navigation import Navigation, constant, proportional, limiter
from telemetry import SetpointTriplet
from util import read_json


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.rtl()
    vehicle.wait_clean()


def range_limit(current, target):
    return limiter(-0.2, 0.2)(proportional(0.1 / 50.0)(current, target))


with pyliner.Pyliner(
    airliner_map=read_json(join(dirname(abspath(__file__)), "cookiecutter.json")),
    ci_port=5009,
    to_port=5012,
    script_name=basename(__file__),
    log_dir=join(dirname(abspath(__file__)), "logs"),
    failure_callback=critical_failure
) as rocky:
    # rocky.atp('Arm')
    rocky.arm()
    # rocky.atp('Takeoff')
    rocky.takeoff()
    rocky.flight_mode(FlightMode.PosCtl)

    rocky.atp('Move Up')
    rocky.nav.up(10, proportional(0.2), tolerance=0.5)

    home = rocky.nav.coordinate
    current = rocky.nav.geographic.pbd(home, 270, 20)

    rocky.buffer_telemetry(SetpointTriplet(
        Cur_Lat=current.latitude,
        Cur_Lon=current.longitude,

    ))

    while rocky.nav.geographic.distance(current, rocky.nav.coordinate) > 1:
        time.sleep(0.1)

    rocky.atp('Return')
    rocky.rtl()
