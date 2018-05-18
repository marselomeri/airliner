import time
from os.path import join, dirname, abspath, basename

import pyliner
from pyliner import FlightMode


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.rtl()
    vehicle.wait_clean()


with pyliner.Pyliner(
    airliner_map=join(dirname(abspath(__file__)), "cookiecutter.json"),
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

    rocky.atp('Start Spiral')
    rocky.fd.y = 0.5
    rocky.fd.z = 0.5
    rocky.fd.r = -0.5

    while rocky.nav.altitude < 510:
        time.sleep(1)
    rocky.fd.zero()

    rocky.atp('Return')
    rocky.rtl()
