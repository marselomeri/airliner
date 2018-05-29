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
from controller import FlightMode
from navigation import proportional, limiter
from time import sleep
from util import read_json


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.cont.rtl()


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
    while rocky.nav.altitude == "NULL":
        sleep(1)
        print "Waiting for telemetry downlink..."
    
    # rocky.cont.atp('Arm')
    rocky.cont.arm()
    # rocky.cont.atp('Takeoff')
    rocky.cont.takeoff()
    rocky.cont.flight_mode(FlightMode.PosCtl)

    rocky.cont.atp('Move Up')
    rocky.nav.up(10, proportional(0.2), tolerance=0.5)

    rocky.cont.atp('First')
    for _ in range(4):
        rocky.nav.forward(5, proportional(0.1))
        rocky.nav.clockwise(90, range_limit)

    rocky.cont.atp('Second')
    for _ in range(4):
        rocky.nav.forward(5, proportional(0.1))
        rocky.nav.counterclockwise(90, range_limit)

    rocky.cont.atp('Third')
    for _ in range(4):
        rocky.nav.backward(5, proportional(0.1))
        rocky.nav.clockwise(90, range_limit)

    rocky.cont.atp('Fourth')
    for _ in range(4):
        rocky.nav.backward(5, proportional(0.1))
        rocky.nav.counterclockwise(90, range_limit)

    rocky.cont.atp('Return')
    rocky.cont.rtl()
