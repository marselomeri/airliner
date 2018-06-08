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
from os.path import basename
from time import sleep

import pyliner
from communication import Communication
from controller import FlightMode
from navigation.control import limiter, proportional
from util import read_json, enable_logging, ScriptingWrapper


def range_limit(current, target):
    return limiter(-0.2, 0.2)(proportional(0.1 / 50.0)(current, target))


enable_logging(script=basename(__file__))

rky = pyliner.Pyliner(
    vehicle_id='rocky',
    communication=Communication(
        airliner_map=read_json("airliner.json"),
        address="192.168.1.2",
        ci_port=5009,
        to_port=5012)
)

with ScriptingWrapper(rky) as rocky:
    while rocky.nav.altitude == "NULL":
        sleep(1)
        print "Waiting for telemetry downlink..."

    rocky.ctrl.atp('Arm')
    rocky.ctrl.arm()
    rocky.ctrl.atp('Takeoff')
    rocky.ctrl.takeoff()
    rocky.ctrl.flight_mode(FlightMode.PosCtl)

    rocky.ctrl.atp('Move Up')
    rocky.nav.vnav(method=proportional(0.2), tolerance=0.5).up(10)

    rocky.nav.defaults['tolerance'] = 0.75
    lnav = rocky.nav.lnav(method=proportional(0.15))
    rocky.nav.defaults['tolerance'] = 2
    yaw = rocky.nav.rotate(method=range_limit)

    rocky.ctrl.atp('First')
    for _ in range(4):
        lnav.forward(5)
        yaw.clockwise(90)

    rocky.ctrl.atp('Second')
    for _ in range(4):
        lnav.forward(5)
        yaw.counterclockwise(90)

    rocky.ctrl.atp('Third')
    for _ in range(4):
        lnav.backward(5)
        yaw.clockwise(90)

    rocky.ctrl.atp('Fourth')
    for _ in range(4):
        lnav.backward(5)
        yaw.counterclockwise(90)

    rocky.ctrl.atp('Return')
    rocky.ctrl.rtl()
