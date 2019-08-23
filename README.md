# Airliner Drone Autopilot

[![Build Status](https://travis-ci.org/WindhoverLabs/airliner.svg?branch=integration%2FWINDEV-758-flight-test-12)](https://travis-ci.org/WindhoverLabs/airliner)

[![Scan Status](https://scan.coverity.com/projects/16394/badge.svg)](https://scan.coverity.com/projects/airliner)

This is the public repository for the [Windhover Labs](https://www.windhoverlabs.com/) drone autopilot Airliner. Airliner is built using [NASA's Core Flight System](https://github.com/nasa/cFS) framework with ported [PX4](https://github.com/PX4/Firmware) flight control algorithms.


## Airliner User/Developer Resources

The [Airliner Wiki](https://hangar.windhoverlabs.com/wiki/display/USR/Welcome) provides general information and technical documention about Airliner. If you wish modify the flight software or contribute to the project please see the [Getting Started](https://hangar.windhoverlabs.com/wiki/display/USR/Getting+Started) page for more detailed information.

### Supported Builds

| Target | Type | Build Status | Coverity Status | Build Command |
| ------ | ---  | ------------ | --------------- | ------------- |
| [Parrot Bebop 2](https://www.parrot.com/us/drones/parrot-bebop-2) | Simulation (SITL) | [![Build Status](https://travis-ci.org/WindhoverLabs/airliner.svg?branch=integration%2FWINDEV-758-flight-test-12)](https://travis-ci.org/WindhoverLabs/airliner) | [![Scan Status](https://scan.coverity.com/projects/16394/badge.svg)](https://scan.coverity.com/projects/airliner) | make bebop2/sitl |
| [Parrot Bebop 2](https://www.parrot.com/us/drones/parrot-bebop-2) | Target | [![Build Status](https://travis-ci.org/WindhoverLabs/airliner.svg?branch=integration%2FWINDEV-758-flight-test-12)](https://travis-ci.org/WindhoverLabs/airliner) | [![Scan Status](https://scan.coverity.com/projects/16394/badge.svg)](https://scan.coverity.com/projects/airliner) | make bebop2/default |
