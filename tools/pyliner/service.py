from sensor import Sensor


class Service(Sensor):
    """Services are long-running passive components to Pyliner.

    A service may be started or stopped at any time by the program. Services
    are not granted control access to the vehicle.

    Service Lifecycle:
        attach -> start -> stop -> detach
    """


