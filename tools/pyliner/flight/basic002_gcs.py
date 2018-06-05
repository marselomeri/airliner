"""
Flies up and down

Requirements Fulfilled:
    PYLINER001
    PYLINER002
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
from navigation import proportional
from util import read_json, enable_logging, ScriptingWrapper

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
    rocky.nav.up(10, proportional(0.2), tolerance=0.5)

    rocky.ctrl.atp('Vertical Right')
    rocky.nav.up(10, proportional(0.2))
    rocky.nav.right(10, proportional(0.1))
    rocky.nav.down(10, proportional(0.25))
    rocky.nav.left(10, proportional(0.1))

    rocky.ctrl.atp('Vertical Left')
    rocky.nav.up(10, proportional(0.2))
    rocky.nav.left(10, proportional(0.1))
    rocky.nav.down(10, proportional(0.25))
    rocky.nav.right(10, proportional(0.1))

    rocky.ctrl.atp('Return')
    rocky.ctrl.rtl()
