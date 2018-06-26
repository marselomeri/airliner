from pyliner.communication import Communication
from pyliner.util import read_json, ScriptingWrapper
from pyliner.vehicle import Vehicle

vehicle = Vehicle(
    vehicle_id='rocky',
    communication=Communication(
        airliner_map=read_json('airliner.json'),
        ci_port=5009, to_port=5012
    )
)

with ScriptingWrapper(vehicle) as rocky:
    geo = rocky.geographic

    rocky.ctrl.atp('Begin Mission')
    rocky.ctrl.arm()
    rocky.ctrl.takeoff()

    last = rocky.nav.position
    last.altitude += 30
    wpts = []
    motion = [(0, 30), (90, 10), (180, 30), (90, 10), (0, 40),
              (315, 40), (270, 20), (180, 10), (90, 30), (135, 10),
              (180, 10), (270, 30), (90, 20), (180, 30)]
    for brng, dist in motion:
        last = geo.pbd(last, brng, dist)
        wpts.append(last)

    rocky.nav.goto(tolerance=1.0)(wpts)

