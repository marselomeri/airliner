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
from time import sleep

from pyliner.communication import Communication
from pyliner.controller import FlightMode
from pyliner.navigation.control import proportional
from pyliner.util import read_json
from pyliner.util.scripting_wrapper import ScriptingWrapper
from pyliner.vehicle import Vehicle

rky = Vehicle(
    vehicle_id='rocky',
    communication=Communication(
        airliner_map=read_json("airliner.json"),
        ci_port=5009,
        to_port=5012)
)

with ScriptingWrapper(rky) as rocky:
    while rocky.nav.altitude == "NULL":
        sleep(1)
        print("Waiting for telemetry downlink...")

    rocky.ctrl.atp('Arm')
    rocky.ctrl.arm()
    rocky.ctrl.atp('Takeoff')
    rocky.ctrl.takeoff()
    rocky.ctrl.flight_mode(FlightMode.PosCtl)

    rocky.ctrl.atp('Move Up')
    rocky.nav.vnav(method=proportional(0.2), tolerance=0.5) \
        .up(10)

    rocky.ctrl.atp('First')
    lnav = rocky.nav.lnav(method=proportional(0.15), tolerance=0.75)
    lnav.forward(5)
    lnav.right(5)
    lnav.backward(5)
    lnav.left(5)

    rocky.ctrl.atp('Second')
    lnav.forward(5)
    lnav.left(5)
    lnav.backward(5)
    lnav.right(5)

    rocky.ctrl.atp('Third')
    rocky.nav.lnav(method=proportional(0.15), tolerance=0.75) \
        .backward(5)\
        .left(5)\
        .forward(5)\
        .right(5)

    rocky.ctrl.atp('Fourth')
    rocky.nav.lnav(method=proportional(0.15), tolerance=0.75) \
        .backward(5).right(5).forward(5).left(5)

    rocky.ctrl.atp('Return')
    rocky.ctrl.rtl()
