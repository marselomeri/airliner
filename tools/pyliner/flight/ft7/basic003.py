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

import pyliner
from pyliner import FlightMode
from navigation import Navigation, constant, proportional, limiter
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

    rocky.atp('First')
    for _ in range(4):
        rocky.nav.forward(5, proportional(0.1))
        rocky.nav.rot_clk(90, range_limit)

    rocky.atp('Second')
    for _ in range(4):
        rocky.nav.forward(5, proportional(0.1))
        rocky.nav.rot_ctr(90, range_limit)

    rocky.atp('Third')
    for _ in range(4):
        rocky.nav.backward(5, proportional(0.1))
        rocky.nav.rot_clk(90, range_limit)

    rocky.atp('Fourth')
    for _ in range(4):
        rocky.nav.backward(5, proportional(0.1))
        rocky.nav.rot_ctr(90, range_limit)

    rocky.atp('Return')
    rocky.rtl()
