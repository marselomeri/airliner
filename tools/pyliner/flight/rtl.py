import time

from pyliner.action import ACTION_RTL
from pyliner.app.communication import Communication
from pyliner.intent import Intent
from pyliner.util import read_json
from pyliner.vehicle import Vehicle

vehicle = Vehicle(
    vehicle_id='rocky',
    communication=Communication(
        airliner_map=read_json('airliner.json'),
        ci_port=5009, to_port=5012
    )
)

vehicle.broadcast(Intent(action=ACTION_RTL))
time.sleep(1)
