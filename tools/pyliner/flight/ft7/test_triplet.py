from os.path import join, dirname, basename, abspath

import pyliner
from navigation import constant
from util import read_json


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.cont.rtl()


rocky = pyliner.Pyliner(
    airliner_map=read_json(join(dirname(abspath(__file__)), "cookiecutter.json")),
    ci_port=5009,
    to_port=5012,
    script_name=basename(__file__),
    log_dir=join(dirname(abspath(__file__)), "logs"),
    failure_callback=critical_failure
)
with rocky as rocky:
    rocky.cont.arm()
    rocky.cont.takeoff()

    rocky.cont.atp('Start')
    dist = 20

    w0 = rocky.nav.position
    w0.altitude = rocky.nav.altitude + 5
    w1 = rocky.geographic.pbd(w0, 0, dist)
    w1.altitude = w0.altitude + 10
    w2 = rocky.geographic.pbd(w1, 90, dist)
    w2.altitude = w1.altitude + 0
    w3 = rocky.geographic.pbd(w2, 180, dist)
    w3.altitude = w2.altitude + 0
    w4 = rocky.geographic.pbd(w3, 270, dist)
    w4.altitude = w3.altitude + 0
    rocky.nav.goto((w0, w1, w2, w3, w4, w0))

    rocky.cont.atp('Return')
    rocky.nav.vnav(to=500, method=constant(-1))
    rocky.cont.rtl()
