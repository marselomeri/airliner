from os.path import join, dirname, abspath, basename

import pyliner
from flight_control_lib import FlightMode
from navigation import Navigation, constant, proportional

with pyliner.Pyliner(
        airliner_map=join(dirname(abspath(__file__)), "cookiecutter.json"),
        ci_port=5009,
        to_port=5012,
        script_name=basename(__file__),
        log_dir=join(dirname(abspath(__file__)), "logs")
) as rocky:
    rocky.enable_module('nav', Navigation)

    # altitude = '/Airliner/CNTL/VehicleGlobalPosition/Alt'
    # rocky.subscribe({'tlm': ['/Airliner/CNTL/VehicleGlobalPosition/Lat',
    #                          '/Airliner/CNTL/VehicleGlobalPosition/Lon',
    #                          altitude,
    #                          '/Airliner/CNTL/VehicleGlobalPosition/Yaw',
    #                          '/Airliner/CNTL/VehicleGlobalPosition/VelN',
    #                          '/Airliner/CNTL/VehicleGlobalPosition/VelE',
    #                          '/Airliner/CNTL/VehicleGlobalPosition/VelD']})
    # rocky.await_fresh(altitude, poll=1, out='Waiting for telemetry downlink...')

    # rocky.atp('Arm')
    rocky.arm()
    # rocky.atp('Takeoff')
    rocky.takeoff()
    rocky.flight_mode(FlightMode.PosCtl)

    rocky.atp('Move Up')
    rocky.nav.up(10, proportional(0.1), tolerance=0.5)

    rocky.atp('First')
    rocky.nav.forward(5)
    rocky.nav.right(5)
    rocky.nav.backward(5)
    rocky.nav.left(5)

    rocky.atp('Second')
    rocky.nav.forward(5)
    rocky.nav.left(5)
    rocky.nav.backward(5)
    rocky.nav.right(5)

    rocky.atp('Third')
    rocky.nav.backward(5)
    rocky.nav.left(5)
    rocky.nav.forward(5)
    rocky.nav.right(5)

    rocky.atp('Fourth')
    rocky.nav.backward(5)
    rocky.nav.right(5)
    rocky.nav.forward(5)
    rocky.nav.left(5)

    rocky.atp('Return')
    rocky.rtl()
