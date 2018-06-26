from os.path import basename
from time import sleep

from pyliner.communication import Communication
from pyliner.navigation.control import proportional
from pyliner.vehicle import Vehicle
from pyliner.util import enable_logging, read_json
from pyliner.util.scripting_wrapper import ScriptingWrapper
from pyliner.util.periodic_executor import PeriodicExecutor

SLEEP = 0.1
HALF_X = 400 / 2
HALF_Y = 400 / 2
TARGET_DISTANCE = 10

# Need to scale [-200, 200] to [-1, 1]
rotator = proportional(1.0 / 200.0)
# Scale distance by some factor
lnav = proportional(1.0 / 10.0)

enable_logging(log_dir='logs', script=basename(__file__))

# TODO OpenCV initialization here


rocky = ScriptingWrapper(Vehicle(
    vehicle_id='rocky',
    communication=Communication(
        airliner_map=read_json("airliner.json"),
        ci_port=5009,
        to_port=5012)
))


def opencv_follow():
    # TODO Get video from rocky
    # x and y in pixels, z in meters
    x, y, z =  # TODO method name

    # Normalize x, y, and z
    x -= HALF_X
    y -= HALF_Y
    z -= TARGET_DISTANCE

    rocky.fd.r = rotator(x)
    # rocky.fd.z = lnav(z) # Uncomment for lateral following


with rocky as rocky:
    while rocky.nav.altitude == "NULL":
        sleep(1)
        print "Waiting for telemetry downlink..."

    rocky.ctrl.atp('Arm')
    rocky.ctrl.arm()
    rocky.ctrl.atp('Takeoff')
    rocky.ctrl.takeoff()

    follow = PeriodicExecutor(
        target=opencv_follow,
        every=SLEEP)

    try:
        follow.start()
        raw_input('Press enter to stop\n')
    except KeyboardInterrupt:
        pass

    follow.stop()
    follow.join()

    rocky.ctrl.rtl()
