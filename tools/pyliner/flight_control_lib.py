from flufl.enum import Enum

from util import get_time


class FlightMode(Enum):
    Manual = 1
    AltCtl = 2
    PosCtl = 3
    RTL = 4


def vehicle_disarm(airliner):
    print "%s: Disarming vehicle" % airliner.script_name
    airliner.log("Disarming vehicle")
    airliner.send_telemetry(
        {'name': '/Airliner/CNTL/ManualSetpoint',
         'args': [
            {'name': 'Timestamp', 'value': get_time()},
            {'name': 'X', 'value': 0.0},
            {'name': 'Y', 'value': 0.0},
            {'name': 'Z', 'value': 0.0},
            {'name': 'R', 'value': 0.0},
            {'name': 'Flaps', 'value': 0.0},
            {'name': 'Aux1', 'value': 0.0},
            {'name': 'Aux2', 'value': 0.0},
            {'name': 'Aux3', 'value': 0.0},
            {'name': 'Aux4', 'value': 0.0},
            {'name': 'Aux5', 'value': 0.0},
            {'name': 'ModeSwitch', 'value': 0},
            {'name': 'ReturnSwitch', 'value': 0},
            {'name': 'RattitudeSwitch', 'value': 0},
            {'name': 'PosctlSwitch', 'value': 0},
            {'name': 'LoiterSwitch', 'value': 0},
            {'name': 'AcroSwitch', 'value': 0},
            {'name': 'OffboardSwitch', 'value': 0},
            {'name': 'KillSwitch', 'value': 0},
            {'name': 'TransitionSwitch', 'value': 0},
            {'name': 'GearSwitch', 'value': 0},
            {'name': 'ArmSwitch', 'value': 3},  # OFF
            {'name': 'StabSwitch', 'value': 0},
            {'name': 'ManSwitch', 'value': 0},
            {'name': 'ModeSlot', 'value': 0},
            {'name': 'DataSource', 'value': 0}]})
