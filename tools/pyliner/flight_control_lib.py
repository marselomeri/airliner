from time import sleep

from flufl.enum import Enum

# Enums
from util import get_time, LogLevel


class FlightMode(Enum):
    Manual = 1
    AltCtl = 2
    PosCtl = 3
    RTL = 4


class Direction(Enum):
    Forward = 1
    Backward = 2
    Left = 3
    Right = 4
    North = 5
    South = 6
    East = 7
    West = 8
    Up = 9


# Flight control commands
def vehicle_move(airliner, direction, speed=0.5, time=1, stop=True,
                 stop_wait=0):
    """
    Router for move commands. Note: speed is stick position percentage,
    not velocity. """

    # Move in the specified direction
    if direction == Direction.Forward:
        vehicle_move_forward(airliner, speed, time)
    elif direction == Direction.Backward:
        vehicle_move_backward(airliner, speed, time)
    elif direction == Direction.Right:
        vehicle_move_right(airliner, speed, time)
    elif direction == Direction.Left:
        vehicle_move_left(airliner, speed, time)
    elif direction == Direction.Up:
        vehicle_move_up(airliner, speed, time)
    else:
        airliner.log("Unknown move direction specified", LogLevel.Error)

    # Execute maneuver for specified duration
    if time:
        sleep(time)

    # If user wants vehicle to stop vehicle after executing maneuver return
    # to stable hover
    if stop:
        vehicle_stable_hover(airliner)
        if stop_wait:
            sleep(stop_wait)


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


def vehicle_stable_hover(airliner):
    airliner.log("Stable hover")
    airliner.send_telemetry(
        {'name': '/Airliner/CNTL/ManualSetpoint',
         'args': [
            {'name': 'Timestamp', 'value': get_time()},
            {'name': 'X', 'value': 0.0},
            {'name': 'Y', 'value': 0.0},
            {'name': 'Z', 'value': 0.5},  # 50% Throttle
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
            {'name': 'PosctlSwitch', 'value': 1},
            {'name': 'LoiterSwitch', 'value': 0},
            {'name': 'AcroSwitch', 'value': 0},
            {'name': 'OffboardSwitch', 'value': 0},
            {'name': 'KillSwitch', 'value': 0},
            {'name': 'TransitionSwitch', 'value': 0},
            {'name': 'GearSwitch', 'value': 1},
            {'name': 'ArmSwitch', 'value': 1},
            {'name': 'StabSwitch', 'value': 0},
            {'name': 'ManSwitch', 'value': 0},
            {'name': 'ModeSlot', 'value': 0},
            {'name': 'DataSource', 'value': 0}]})


def vehicle_move_forward(airliner, percent_speed, time):
    print "%s: moving forward at %s%% for %s seconds" % (
        airliner.script_name, percent_speed * 100, time)
    airliner.log(
        "Moving forward at %s%% for %s seconds" % (percent_speed, time))
    airliner.send_telemetry(
        {'name': '/Airliner/CNTL/ManualSetpoint', 'args': [
            {'name': 'Timestamp', 'value': get_time()},
            {'name': 'X', 'value': percent_speed},
            {'name': 'Y', 'value': 0.0},
            {'name': 'Z', 'value': 0.5},
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
            {'name': 'PosctlSwitch', 'value': 1},
            {'name': 'LoiterSwitch', 'value': 0},
            {'name': 'AcroSwitch', 'value': 0},
            {'name': 'OffboardSwitch', 'value': 0},
            {'name': 'KillSwitch', 'value': 0},
            {'name': 'TransitionSwitch', 'value': 0},
            {'name': 'GearSwitch', 'value': 1},
            {'name': 'ArmSwitch', 'value': 1},
            {'name': 'StabSwitch', 'value': 0},
            {'name': 'ManSwitch', 'value': 0},
            {'name': 'ModeSlot', 'value': 0},
            {'name': 'DataSource', 'value': 0}]})


def vehicle_move_left(airliner, percent_speed, time):
    print "%s: moving left at %s%% for %s seconds" % (
        airliner.script_name, percent_speed * 100, time)
    airliner.log("Moving left at %s%% for %s seconds" % (percent_speed, time))
    airliner.send_telemetry(
        {'name': '/Airliner/CNTL/ManualSetpoint', 'args': [
            {'name': 'Timestamp', 'value': get_time()},
            {'name': 'X', 'value': 0.0},
            {'name': 'Y', 'value': -percent_speed},
            {'name': 'Z', 'value': 0.5},
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
            {'name': 'PosctlSwitch', 'value': 1},
            {'name': 'LoiterSwitch', 'value': 0},
            {'name': 'AcroSwitch', 'value': 0},
            {'name': 'OffboardSwitch', 'value': 0},
            {'name': 'KillSwitch', 'value': 0},
            {'name': 'TransitionSwitch', 'value': 0},
            {'name': 'GearSwitch', 'value': 1},
            {'name': 'ArmSwitch', 'value': 1},
            {'name': 'StabSwitch', 'value': 0},
            {'name': 'ManSwitch', 'value': 0},
            {'name': 'ModeSlot', 'value': 0},
            {'name': 'DataSource', 'value': 0}]})


def vehicle_move_backward(airliner, percent_speed, time):
    print "%s: moving backward at %s%% for %s seconds" % (
        airliner.script_name, percent_speed * 100, time)
    airliner.log(
        "Moving backward at %s%% for %s seconds" % (percent_speed, time))
    airliner.send_telemetry(
        {'name': '/Airliner/CNTL/ManualSetpoint', 'args': [
            {'name': 'Timestamp', 'value': get_time()},
            {'name': 'X', 'value': -percent_speed},
            {'name': 'Y', 'value': 0.0},
            {'name': 'Z', 'value': 0.5},
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
            {'name': 'PosctlSwitch', 'value': 1},
            {'name': 'LoiterSwitch', 'value': 0},
            {'name': 'AcroSwitch', 'value': 0},
            {'name': 'OffboardSwitch', 'value': 0},
            {'name': 'KillSwitch', 'value': 0},
            {'name': 'TransitionSwitch', 'value': 0},
            {'name': 'GearSwitch', 'value': 1},
            {'name': 'ArmSwitch', 'value': 1},
            {'name': 'StabSwitch', 'value': 0},
            {'name': 'ManSwitch', 'value': 0},
            {'name': 'ModeSlot', 'value': 0},
            {'name': 'DataSource', 'value': 0}]})


def vehicle_move_right(airliner, percent_speed, time):
    print "%s: moving right at %s%% for %s seconds" % (
        airliner.script_name, percent_speed * 100, time)
    airliner.log("Moving right at %s%% for %s seconds" % (percent_speed, time))
    airliner.send_telemetry(
        {'name': '/Airliner/CNTL/ManualSetpoint', 'args': [
            {'name': 'Timestamp', 'value': get_time()},
            {'name': 'X', 'value': 0.0},
            {'name': 'Y', 'value': percent_speed},
            {'name': 'Z', 'value': 0.5},
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
            {'name': 'PosctlSwitch', 'value': 1},
            {'name': 'LoiterSwitch', 'value': 0},
            {'name': 'AcroSwitch', 'value': 0},
            {'name': 'OffboardSwitch', 'value': 0},
            {'name': 'KillSwitch', 'value': 0},
            {'name': 'TransitionSwitch', 'value': 0},
            {'name': 'GearSwitch', 'value': 1},
            {'name': 'ArmSwitch', 'value': 1},
            {'name': 'StabSwitch', 'value': 0},
            {'name': 'ManSwitch', 'value': 0},
            {'name': 'ModeSlot', 'value': 0},
            {'name': 'DataSource', 'value': 0}]})


def vehicle_move_up(airliner, percent_speed, time):
    print "%s: moving up at %s%% for %s seconds" % (
        airliner.script_name, percent_speed * 100, time)
    airliner.log("Moving up at %s%% for %s seconds" % (percent_speed, time))
    airliner.send_telemetry(
        {'name': '/Airliner/CNTL/ManualSetpoint', 'args': [
            {'name': 'Timestamp', 'value': get_time()},
            {'name': 'X', 'value': 0.0},
            {'name': 'Y', 'value': 0.0},
            {'name': 'Z', 'value': 0.5 + (percent_speed * .5)},
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
            {'name': 'PosctlSwitch', 'value': 1},
            {'name': 'LoiterSwitch', 'value': 0},
            {'name': 'AcroSwitch', 'value': 0},
            {'name': 'OffboardSwitch', 'value': 0},
            {'name': 'KillSwitch', 'value': 0},
            {'name': 'TransitionSwitch', 'value': 0},
            {'name': 'GearSwitch', 'value': 1},
            {'name': 'ArmSwitch', 'value': 1},
            {'name': 'StabSwitch', 'value': 0},
            {'name': 'ManSwitch', 'value': 0},
            {'name': 'ModeSlot', 'value': 0},
            {'name': 'DataSource', 'value': 0}]})

