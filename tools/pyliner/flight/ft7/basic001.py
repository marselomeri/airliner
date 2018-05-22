"""
Flies forward, backward, left, and right.

Requirements Fulfilled:
    PYLINER001
    PYLINER002
    PYLINER003
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
from navigation import Navigation, constant, proportional
from util import read_json


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.rtl()
    vehicle.wait_clean()


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
    rocky.nav.forward(5, proportional(0.1))
    rocky.nav.right(5, proportional(0.1))
    rocky.nav.backward(5, proportional(0.1))
    rocky.nav.left(5, proportional(0.1))

    rocky.atp('Second')
    rocky.nav.forward(5, proportional(0.1))
    rocky.nav.left(5, proportional(0.1))
    rocky.nav.backward(5, proportional(0.1))
    rocky.nav.right(5, proportional(0.1))

    rocky.atp('Third')
    rocky.nav.backward(5, proportional(0.1))
    rocky.nav.left(5, proportional(0.1))
    rocky.nav.forward(5, proportional(0.1))
    rocky.nav.right(5, proportional(0.1))

    rocky.atp('Fourth')
    rocky.nav.backward(5, proportional(0.1))
    rocky.nav.right(5, proportional(0.1))
    rocky.nav.forward(5, proportional(0.1))
    rocky.nav.left(5, proportional(0.1))

    rocky.atp('Return')
    rocky.rtl()
