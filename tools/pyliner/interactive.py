from os.path import join, dirname, basename, abspath

import pyliner
from navigation import constant, limiter, proportional
from util import read_json

rocky = pyliner.Pyliner(
    airliner_map=read_json(join(dirname(abspath(__file__)), "airliner.json")),
    ci_port=5009,
    to_port=5012,
    script_name=basename(__file__),
    log_dir=join(dirname(abspath(__file__)), "logs")
)
