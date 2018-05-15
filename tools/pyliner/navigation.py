from pyliner_module import PylinerModule


class Navigation(PylinerModule):
    """Navigation module. Contains all navigation features."""

    req_telem = (
        ('lat', '/Airliner/CNTL/VehicleGlobalPosition/Lat'),
        ('lon', '/Airliner/CNTL/VehicleGlobalPosition/Lon'),
        ('alt', '/Airliner/CNTL/VehicleGlobalPosition/Alt'),
        ('yaw', '/Airliner/CNTL/VehicleGlobalPosition/Yaw'),
        ('velN', '/Airliner/CNTL/VehicleGlobalPosition/VelN'),
        ('velE', '/Airliner/CNTL/VehicleGlobalPosition/VelE'),
        ('velD', '/Airliner/CNTL/VehicleGlobalPosition/VelD')
    )

    def __init__(self, vehicle):
        super(Navigation, self).__init__(vehicle)

    @classmethod
    def required_telemetry(cls):
        return cls.req_telem


