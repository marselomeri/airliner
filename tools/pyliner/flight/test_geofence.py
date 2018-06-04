from os.path import basename
from time import sleep

import pyliner
from communication import Communication
from geofence import Geofence, VerticalCylinder
from util import read_json, enable_logging, ScriptingWrapper

enable_logging(script=basename(__file__))

rky = pyliner.Pyliner(
    vehicle_id='001',
    communication=Communication(
        airliner_map=read_json("airliner.json"),
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
    # rocky.ctrl.flight_mode(FlightMode.PosCtl)

    rocky.ctrl.atp('Enable Fence')
    fence = rocky.fence  # type: Geofence
    base = fence.layers[0]
    base.add(VerticalCylinder(
        rocky.geographic, rocky.nav.position,
        low=rocky.nav.altitude - 10, high=rocky.nav.altitude + 100, radius=20))
    fence.enabled = True

    rocky.ctrl.atp('Start mission')
    home = rocky.nav.position
    new = rocky.geographic.pbd(home, 90, 15)
    new.altitude = rocky.nav.altitude + 10
    rocky.nav.goto(new)

    new = rocky.geographic.pbd(new, 0, 20)
    rocky.nav.goto(new)

    rocky.ctrl.atp('Return (if you got here the fence failed)')
    rocky.ctrl.rtl()
