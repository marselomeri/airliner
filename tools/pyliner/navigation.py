from collections import namedtuple
from numbers import Number, Real

import time

from pyliner_module import PylinerModule
from util import get_time


def constant(value):
    return lambda current, target: value


def proportional(const, neutral=0.5):
    return lambda current, target: (target - current) * const + neutral


# LatLon = namedtuple('LatLon', ['latitude', 'longitude'])


class Navigation(PylinerModule):
    """Navigation module. Contains all navigation features.
    
    Note:
        Currently this module takes lateral and vertical navigation as separate
        components, and only executes one at a time. 
    TODO: In a future version a more integrated 3d-space will be implemented.
    """

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

    def down(self, amount, method=None, tolerance=1):
        self.vnav(by=-amount, method=method, tolerance=tolerance)

    def send_telemetry(self, **kwargs):
        telem_dict = {
            'Timestamp': get_time(), 'X': 0.0, 'Y': 0.0, 'Z': 0.5, 'R': 0.0,
            'Flaps': 0.0, 'Aux1': 0.0, 'Aux2': 0.0, 'Aux3': 0.0, 'Aux4': 0.0,
            'Aux5': 0.0, 'ModeSwitch': 0, 'ReturnSwitch': 0,
            'RattitudeSwitch': 0, 'PosctlSwitch': 1, 'LoiterSwitch': 0,
            'AcroSwitch': 0, 'OffboardSwitch': 0, 'KillSwitch': 0,
            'TransitionSwitch': 0, 'GearSwitch': 1, 'ArmSwitch': 1,
            'StabSwitch': 0, 'ManSwitch': 0, 'ModeSlot': 0, 'DataSource': 0
        }
        telem_dict.update(kwargs)
        self.vehicle.com.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [{'name': name, 'value': value} for name, value in
                      telem_dict.items()]}
        )

    @classmethod
    def required_telemetry_paths(cls):
        return cls.req_telem.values()

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
        while (target_altitude - self.altitude) > tolerance:
            new_z = method(self.altitude, target_altitude)
            capped_z = min(max(new_z, -1), 1)
            self.send_telemetry(Z=capped_z)
            time.sleep(1 / 32)
        self.send_telemetry(Z=0.5)
