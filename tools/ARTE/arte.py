#!/usr/bin/env python3
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
from arte_server import ArteServerGlobals
from arte_test import ArteTestFixture
from arte_events import ArteEventHandler

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


def count_clients(config):
    client_count = 0
    for i in config['clients']:
        client_count += 1
    return client_count


def main():
    ArteSplash()
    
    parser = argparse.ArgumentParser()
    parser.add_argument('configpath', help="specify path to the configuration file")
    args = parser.parse_args()
    
    # Check the path to the configuration file
    check_path(args.configpath)

    # TODO write a helper function to verify the config file
    # Open and decode the configuration file
    with open(args.configpath) as config_file:
        config = json.load(config_file)
        
    # Count the number of clients specified in the config file
    client_count = count_clients(config)
    
    
    my_event_handler = ArteEventHandler()
    
    my_server = ArteServer("localhost", 9999, client_count, my_event_handler)

    my_test_fixture = ArteTestFixture("test1", config, my_event_handler)
    
    # TODO move to logging
    print("client count = ", my_test_fixture.client_count)
    
    # startup the clients
    my_event_handler.startup()
     
    # wait on a shutdown event or timeout
    # this timeout needs to be changed to a watchdog that gets kicked.
    if ArteServerGlobals.shutdown_notification.wait(my_test_fixture.timeout):
        # A shutdown request was received from a client.
        my_event_handler.shutdown()
        sys.exit(0)
    
    # The event wait returned false so a timeout was reached.
    # Shutdown the server.
    print ("configured timeout reached")

    # Terminate clients.
    my_event_handler.shutdown()
    sys.exit(0)

if __name__ == '__main__':
    main()
