import time

from pyliner.communication import Communication
from pyliner.util import read_json
from pyliner.vehicle import Vehicle

vehicle = Vehicle(
    vehicle_id='rocky',
    communication=Communication(
        airliner_map=read_json('airliner.json'),
        ci_port=5009, to_port=5012
    )
)

vehicle.components['app']['ctrl']._component.rtl()
time.sleep(1)
