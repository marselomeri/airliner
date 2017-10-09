"""

   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.
 3. Neither the name Windhover Labs nor the names of its 
    contributors may be used to endorse or promote products derived 
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

"""
from arte_config import ArteSplash
from arte_launcher import ArteSubprocess
from arte_server import ArteServer
from arte_test import ArteTestFixture

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
    ArteSplash()
    
    parser = argparse.ArgumentParser()
    parser.add_argument('configpath', help="specify path to the configuration file")
    args = parser.parse_args()
    
    # Check the path to the configuration file
    check_path(args.configpath)
    
    # Open and decode the configuration file
    with open(args.configpath) as config_file:
        config = json.load(config_file)
        
    # TODO write a helper function to verify the config file
    my_test_fixture = ArteTestFixture("test1", config)
    
    server = ArteServer("localhost", 9999, my_test_fixture.client_count)
    
    # startup the clients
    my_test_fixture.test_run()
    
    # The test fixture returned so a timeout was reached.
    # Shutdown the server.
    server.server_shutdown()
    
    # Terminate clients.
    my_test_fixture.test_teardown()
    sys.exit(0)

if __name__ == '__main__':
    main()
