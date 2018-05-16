from numbers import Number, Real

import time

from pyliner_module import PylinerModule
from util import get_time


def constant(value):
    return lambda current, target: value


def proportional(const, neutral=0.5):
    return lambda current, target: (target - current) * const + neutral


class Navigation(PylinerModule):
    """Navigation module. Contains all navigation features."""

    req_telem = {
        'latitude': '/Airliner/CNTL/VehicleGlobalPosition/Lat',
        'longitude': '/Airliner/CNTL/VehicleGlobalPosition/Lon',
        'altitude': '/Airliner/CNTL/VehicleGlobalPosition/Alt',
        'yaw': '/Airliner/CNTL/VehicleGlobalPosition/Yaw',
        'velN': '/Airliner/CNTL/VehicleGlobalPosition/VelN',
        'velE': '/Airliner/CNTL/VehicleGlobalPosition/VelE',
        'velD': '/Airliner/CNTL/VehicleGlobalPosition/VelD'
    }

    # Public Navigation Properties
    latitude = property(PylinerModule.telem(req_telem['latitude']))
    longitude = property(PylinerModule.telem(req_telem['longitude']))
    altitude = property(PylinerModule.telem(req_telem['altitude']))
    yaw = property(PylinerModule.telem(req_telem['yaw']))

    @classmethod
    def required_telemetry_paths(cls):
        return cls.req_telem.values()

    def down(self, amount, method=None, tolerance=1):
        self.vnav(by=-amount, method=method, tolerance=tolerance)

    def up(self, amount, method=None, tolerance=1):
        self.vnav(by=amount, method=method, tolerance=tolerance)

    def vnav(self, by=None, to=None, method=None, tolerance=1):
        if not any((by, to)):
            raise ValueError('Must set either by or to.')
        elif by and to:
            raise ValueError('Cannot set both by and to.')
        if not method:
            raise ValueError('Must have navigation method.')
        if not isinstance(tolerance, Real) or tolerance <= 0:
            raise ValueError('Tolerance must be set to a real positive number.')
        target_altitude = self.altitude + by if by else to
        i = 0
        while (target_altitude - self.altitude) > tolerance:
            new_z = method(self.altitude, target_altitude)
            capped_z = min(max(new_z, -1), 1)
            self.vehicle.send_telemetry(
                {'name': '/Airliner/CNTL/ManualSetpoint',
                 'args': [
                     {'name': 'Timestamp', 'value': get_time()},
                     {'name': 'X', 'value': 0.0},
                     {'name': 'Y', 'value': 0.0},
                     {'name': 'Z', 'value': capped_z},
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
                     {'name': 'GearSwitch', 'value': 3},
                     {'name': 'ArmSwitch', 'value': 1},
                     {'name': 'StabSwitch', 'value': 0},
                     {'name': 'ManSwitch', 'value': 0},
                     {'name': 'ModeSlot', 'value': 0},
                     {'name': 'DataSource', 'value': 0}]})
            time.sleep(1/32)
        self.vehicle.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
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
                 {'name': 'GearSwitch', 'value': 3},
                 {'name': 'ArmSwitch', 'value': 1},
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})
