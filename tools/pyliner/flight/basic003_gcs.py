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
from time import sleep

from pyliner.app.communication import Communication
from pyliner.app.controller import FlightMode
from pyliner.navigation.control import limiter, proportional
from pyliner.vehicle import Vehicle
from pyliner.util import read_json
from pyliner.util.scripting_wrapper import ScriptingWrapper


def range_limit(current, target):
    return limiter(-0.2, 0.2)(proportional(0.1 / 50.0)(current, target))


rky = Vehicle(
    vehicle_id='rocky',
    communications=Communication(
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

    lnav = rocky.nav.lnav(method=proportional(0.15), tolerance=0.75)
    yaw = rocky.nav.rotate(method=range_limit, tolerance=2)

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
