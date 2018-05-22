"""
Fly in a figure-8. Fly at full-speed during approach and retreat, and slow down
during the turn to allow for a smaller turn radius.

Requirements Fulfilled:
    PYLINER001
    PYLINER003
    PYLINER004
    PYLINER006
    PYLINER009
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
from pyliner import FlightMode
from navigation import Navigation, constant, proportional, limiter
from util import read_json


def range_limit(current, target):
    return limiter(0, 0.25)(proportional(0.1 / 50.0)(current, target))


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.rtl()
    vehicle.wait_clean()


with pyliner.Pyliner(
    airliner_map=read_json(join(dirname(abspath(__file__)), "cookiecutter.json")),
    ci_port=5009,
    to_port=5012,
    script_name=basename(__file__),
    log_dir=join(dirname(abspath(__file__)), "logs"),
    failure_callback=critical_failure
) as rocky:
    # rocky.atp('Arm')
    rocky.arm()
    # rocky.atp('Takeoff')
    rocky.takeoff()
    rocky.flight_mode(FlightMode.PosCtl)

    home = rocky.nav.coordinate

    rocky.nav.vnav(to=500, method=constant(1.0))

    rocky.fd.x = 1.0
    direction = -1

    while True:
        # Wait until close to home
        print('Approach')
        while rocky.nav.geographic.distance(home, rocky.nav.coordinate) > 7:
            sleep(0.1)

        # Wait until away from home
        print('Retreat')
        while rocky.nav.geographic.distance(home, rocky.nav.coordinate) < 7:
            sleep(0.1)

        print('Rotate')
        # Flip directions
        rocky.fd.x = 5.0 / 8.0
        direction *= -1

        # Face home
        def home_bear():
            return rocky.nav.geographic.bearing(rocky.nav.coordinate, home)

        diff = float('inf')
        while diff > 2:
            bear = home_bear()
            diff = rocky.nav.heading - bear
            diff = diff % 360  # if diff > 0 else -(diff % 360)
            diff = diff if diff < 180 else -(diff - 360)
            rocky.fd.r = abs(limiter(-0.25, 0.25)(diff / 150)) * direction
            # print('{:3} - {:3} = {:3}: {:3}'.format(
            #     round(bear, 2),
            #     round(rocky.nav.heading, 2),
            #     round(diff, 2),
            #     round(rocky.fd.r, 2)
            # ))
            sleep(0.1)

        # Stop rotating
        rocky.fd.x = 0.75
        rocky.fd.r = 0.0
