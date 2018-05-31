"""
Fly a heading and to a waypoint.

Requirements Fulfilled:
    PYLINER001
    PYLINER002
    PYLINER003
    PYLINER004
    PYLINER005
    PYLINER006
    PYLINER010
    PYLINER011
    PYLINER012
    PYLINER013
    PYLINER014
    PYLINER016
"""

from os.path import join, dirname, abspath, basename
from time import sleep

import pyliner
from navigation import proportional, limiter
from util import read_json


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.cont.rtl()


def range_limit(current, target):
    return limiter(-0.2, 0.2)(proportional(0.1 / 50.0)(current, target))


with pyliner.Pyliner(
    airliner_map=read_json(join(dirname(abspath(__file__)), "cookiecutter.json")),
    address="192.168.1.2",
    ci_port=5009,
    to_port=5012,
    script_name=basename(__file__),
    log_dir=join(dirname(abspath(__file__)), "logs"),
    failure_callback=critical_failure
) as rocky:
    while rocky.nav.altitude == "NULL":
        sleep(1)
        print "Waiting for telemetry downlink..."
    
    rocky.cont.atp('Arm')
    rocky.cont.arm()
    rocky.cont.atp('Takeoff')
    rocky.cont.takeoff()
    # rocky.cont.flight_mode(FlightMode.PosCtl)

    rocky.cont.atp('Goto')

    home = rocky.nav.position
    new = rocky.geographic.pbd(home, 90, 20)
    new.altitude = rocky.nav.altitude + 10

    rocky.nav.goto(new)
    rocky.nav.goto(rocky.geographic.pbd(new, 270, 40))

    rocky.cont.atp('Return')
    rocky.cont.rtl()
