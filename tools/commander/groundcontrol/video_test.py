import sys
import time
sys.path.insert(0,'/home/vagrant/git/airliner/tools/pyliner')
from pyliner import *


airliner = Pyliner(**{"airliner_map": "/home/vagrant/git/airliner/tools/pyliner/cookiecutter.json",
                      "ci_port": 5009,
                      "to_port": 5012,
                      "script_name": "demo_test",
                      "log_dir": "./logs/"})


def callback_func(data):
    print "Current telemetry value: " + data['value']


airliner.subscribe({'tlm': ['/Airliner/ES/HK/CmdCounter']}, callback_func)
