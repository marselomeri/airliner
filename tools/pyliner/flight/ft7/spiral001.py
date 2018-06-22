"""
Fly in a rising spiral.

Requirements Fulfilled:
    PYLINER001
    PYLINER003
    PYLINER004
    PYLINER009
    PYLINER010
    PYLINER011
    PYLINER012
    PYLINER013
    PYLINER014
    PYLINER016
"""
import time
from os.path import join, dirname, abspath, basename

import pyliner
from controller import FlightMode
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
    # rocky.cont.atp('Arm')
    rocky.cont.arm()
    # rocky.cont.atp('Takeoff')
    rocky.cont.takeoff()
    rocky.cont.flight_mode(FlightMode.PosCtl)

    rocky.cont.atp('Start Spiral')
    rocky.fd.y = 0.5
    rocky.fd.z = 0.5
    rocky.fd.r = -0.5

    while rocky.nav.altitude < 510:
        time.sleep(1)
    rocky.fd.zero()

    rocky.cont.atp('Return')
    rocky.cont.rtl()
