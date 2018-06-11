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

from pyliner.communication import Communication
from pyliner.controller import FlightMode
from pyliner.navigation.control import proportional
from pyliner.pyliner import Pyliner
from pyliner.util import read_json, enable_logging, ScriptingWrapper

enable_logging(log_dir='logs', script=basename(__file__))

rky = Pyliner(
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

    vnav = rocky.nav.vnav(method=proportional(0.2), tolerance=0.5)
    lnav = rocky.nav.lnav(method=proportional(0.15), tolerance=0.75)

    rocky.ctrl.atp('Move Up')
    vnav.up(10)

    rocky.ctrl.atp('Vertical Right')
    vnav.up(5)
    lnav.right(5)
    vnav.down(5, method=proportional(0.25))
    lnav.left(5)

    rocky.ctrl.atp('Vertical Left')
    vnav.up(5)
    lnav.left(5)
    vnav.down(5, method=proportional(0.25))
    lnav.right(5)

    rocky.ctrl.atp('Return')
    rocky.ctrl.rtl()
