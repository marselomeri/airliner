from arte_config import arte_splash
from arte_launcher import arte_subprocess
from arte_server import arte_server
from arte_test import test_fixture

import time
import argparse
import os
import sys
import json


def path_exists(file_path):
    if not os.path.exists(file_path):
        return False
    else:
        return True


def check_path(file_path):
    if path_exists(file_path):
        print ("Configuration file resolved:", str(file_path))
    else:
        sys.exit("Configuration file not found: " + str(file_path))


def main():
    arte_splash()
    
    parser = argparse.ArgumentParser()
    parser.add_argument('configpath', help="specify path to the configuration file")
    args = parser.parse_args()
    
    # Check the path to the configuration file
    check_path(args.configpath)
    
    # Open and decode the configuration file
    with open(args.configpath) as config_file:
        config = json.load(config_file)
        
    # TODO write a helper function to verify the config file
    my_test_fixture = test_fixture("test1", config)
    
    server = arte_server("localhost", 9999)
    
    my_test_fixture.test_run()


if __name__ == '__main__':
    main()
