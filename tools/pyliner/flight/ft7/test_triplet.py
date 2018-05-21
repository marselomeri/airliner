from os.path import join, dirname, basename, abspath

import time

import pyliner
from navigation import constant
from telemetry import SetpointTriplet
from util import read_json


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.rtl()
    vehicle.wait_clean()


rocky = pyliner.Pyliner(
    airliner_map=read_json(join(dirname(abspath(__file__)), "cookiecutter.json")),
    ci_port=5009,
    to_port=5012,
    script_name=basename(__file__),
    log_dir=join(dirname(abspath(__file__)), "logs"),
    failure_callback=critical_failure
)
with rocky as rocky:
    rocky.arm()
    rocky.takeoff()

    rocky.atp('Start')

    waypoints = [(rocky.nav.coordinate, 495)]
    waypoints.append(
        (rocky.nav.geographic.pbd(waypoints[-1][0], 0, 50), 500))
    waypoints.append(
        (rocky.nav.geographic.pbd(waypoints[-1][0], 90, 50), 510))
    waypoints.append(
        (rocky.nav.geographic.pbd(waypoints[-1][0], 180, 50), 520))
    waypoints.append(
        (rocky.nav.geographic.pbd(waypoints[-1][0], 270, 50), 530))
    waypoints.append(waypoints[0])

    def triplet(prev, cur, nxt):
        return SetpointTriplet(
            Prev_Lat=prev[0].latitude,
            Prev_Lon=prev[0].longitude,
            Prev_Alt=prev[1],
            Prev_PositionValid=1,
            Prev_Valid=1,
            Cur_Lat=cur[0].latitude,
            Cur_Lon=cur[0].longitude,
            Cur_Alt=cur[1],
            Cur_PositionValid=1,
            Cur_Valid=1,
            Next_Lat=nxt[0].latitude,
            Next_Lon=nxt[0].longitude,
            Next_Alt=nxt[1],
            Next_PositionValid=1,
            Next_Valid=1)

    def collector(iter):
        s1 = None
        s2 = next(iter)
        s3 = next(iter)
        while True:
            s1 = s2
            s2 = s3
            s3 = next(iter)
            yield s1, s2, s3

    for prev, cur, nxt in collector(iter(waypoints)):
        rocky.com.send_telemetry(triplet(prev, cur, nxt))
        while rocky.nav.geographic.distance(cur[0], rocky.nav.coordinate) > 1:
            time.sleep(1 / 10)

    rocky.atp('Return')
    rocky.nav.vnav(to=500, method=constant(-1))
    rocky.rtl()
