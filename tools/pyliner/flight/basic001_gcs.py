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
from time import sleep

import pyliner
from controller import FlightMode
from navigation import proportional
from util import read_json


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.ctrl.rtl()


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
    
    rocky.ctrl.atp('Arm')
    rocky.ctrl.arm()
    rocky.ctrl.atp('Takeoff')
    rocky.ctrl.takeoff()
    rocky.ctrl.flight_mode(FlightMode.PosCtl)

    rocky.ctrl.atp('Move Up')
    rocky.nav.up(10, proportional(0.2), tolerance=0.5)

    rocky.ctrl.atp('First')
    rocky.nav.forward(5, proportional(0.1))
    rocky.nav.right(5, proportional(0.1))
    rocky.nav.backward(5, proportional(0.1))
    rocky.nav.left(5, proportional(0.1))

    rocky.ctrl.atp('Second')
    rocky.nav.forward(5, proportional(0.1))
    rocky.nav.left(5, proportional(0.1))
    rocky.nav.backward(5, proportional(0.1))
    rocky.nav.right(5, proportional(0.1))

    rocky.ctrl.atp('Third')
    rocky.nav.backward(5, proportional(0.1))
    rocky.nav.left(5, proportional(0.1))
    rocky.nav.forward(5, proportional(0.1))
    rocky.nav.right(5, proportional(0.1))

    rocky.ctrl.atp('Fourth')
    rocky.nav.backward(5, proportional(0.1))
    rocky.nav.right(5, proportional(0.1))
    rocky.nav.forward(5, proportional(0.1))
    rocky.nav.left(5, proportional(0.1))

    rocky.ctrl.atp('Return')
    rocky.ctrl.rtl()
