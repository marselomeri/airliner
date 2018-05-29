from os.path import join, dirname, abspath, basename

import pyliner
from geofence import Geofence, VerticalCylinder
from util import read_json


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.cont.rtl()


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
    # rocky.atp('Takeoff')
    rocky.cont.takeoff()
    # rocky.cont.flight_mode(FlightMode.PosCtl)

    rocky.cont.atp('Enable Fence')
    fence = rocky.fence  # type: Geofence
    base = fence.layers[0]
    base.add_volume(VerticalCylinder(
        rocky.geographic, rocky.nav.position,
        low_altitude=rocky.nav.altitude - 10, high_altitude=rocky.nav.altitude + 100, radius=20))
    fence.enabled = True

    home = rocky.nav.position
    new = rocky.geographic.pbd(home, 90, 15)
    new.altitude = rocky.nav.altitude + 10
    rocky.nav.goto(new)

    new = rocky.geographic.pbd(new, 0, 20)
    rocky.nav.goto(new)

    rocky.cont.atp('Return (if you got here the fence failed)')
    rocky.cont.rtl()
