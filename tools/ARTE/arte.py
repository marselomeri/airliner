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
from arte_test import ArteTestFixture
from arte_events import ArteEventHandler

import time
import argparse
import os
import sys
import json
import logging


def path_exists(file_path):
    """Check if a path exists.
    
    Args: 
        file_path (path): The path to the configuration file.
    
    Returns:
        boolean: True for success, otherwise failure.
    """
    if not os.path.exists(file_path):
        return False
    else:
        return True


def check_path(file_path):
    """Check if the configuration file exists.
    
    Args:
        file_path (path): The path to the configuration file.

    Note:
        Exits with a string notification that the path could not be 
        resolved.
    """
    if path_exists(file_path):
        logging.info('Configuration file resolved %s', str(file_path))
    else:
        sys.exit("Configuration file not found: " + str(file_path))


def count_clients(config):
    """Count the number of clients in the deserialized configuration.

    Args:
        config (:obj:`deserialized JSON`): The deserialized JSON 
            configuration file.

    Returns:
        unsigned int: the number of clients counted.
    """
    
    client_count = 0
    for i in config['clients']:
        # If Arte client == true
        if i['client'] == 1:
            client_count += 1
    return client_count


def get_timeouts(config):
    """Get the value of timeouts in the configuration file.
    
    Note:
        timeouts is for generic timeouts i.e. anything that could pend
        forever like recv.

    Args:
        config (:obj:`deserialized JSON`): The deserialized JSON 
            configuration file.
        
    Returns:
        unsigned int: the timeout in seconds as specified in the 
            configuration file.
     """
    return config['timeouts']


def get_timeout(config):
    """Get the value of timeout in the configuration file.

    Note:
        timeout is the overall timeout for all test(s). This value 
            needs to be greater than the maximum amount of time test(s)
            could take.

    Args:
        config (:obj:`deserialized JSON`): The deserialized JSON 
            configuration file.

    Returns:
        uint: the timeout in seconds as specified in the 
            configuration file.
     """
    return config['timeout']


def get_watchdog(config):
    """Get the value of the watchdog timeout in the configuration file.

    Note:
        watchdog is the timeout for all watchdog timers. This value 
        needs to be greater than the maximum amount of time any 
        thread would take before resetting its watchdog. The same 
        goes for any task that is assigned a watchdog.

    Args:
        config (:obj:`deserialized JSON`): The deserialized JSON 
            configuration file.

    Returns:
        uint: the timeout in seconds as specified in the 
            configuration file.
     """
    return config['watchdog']


def get_majorframe(config):
    """Get the minor in major frame count from the configuration file.

    Note:
        Default value is 200.

    Args:
        config (:obj:`deserialized JSON`): The deserialized JSON 
            configuration file.

    Returns:
        uint: the number of minor frames in a major frame.
     """
    return config['majorframe']


def get_realtime(config):
    """Get the realtime configuration value from the configuration file.

    Note:
        ARTE server is not started in realtime mode.

    Args:
        config (:obj:`deserialized JSON`): The deserialized JSON 
            configuration file.

    Returns:
        Boolean: false for faster than realtime, true for realtime.
     """
    return config['realtime']


def get_resetterm(config):
    """Get the reset terminal value from the configuration file.

    Note:
        Some applications launched with ARTE may leave the terminal in 
        an abnormal state. Optionally reset the terminal on exit. 
        Terminal output printed to stdout is lost.

    Args:
        config (:obj:`deserialized JSON`): The deserialized JSON 
            configuration file.

    Returns:
        Boolean: true to reset, false for no reset.
     """
    return config['resetterm']


def main():
    """The entry point for ARTE.
    
    Exit status codes:
        0: A client shutdown requests returned success.
        1: The main timeout was reached.
        2: The watchdog timeout was reached.
        3: A shutdown requests was received with an unknown status.
        4: A socket error caused an early shutdown.
        
    """
    logging.basicConfig(level=logging.DEBUG)

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
    logging.info('client count %d', client_count)
    
    # Get the configured timeouts value for things like recv etc
    timeouts = get_timeouts(config)
    
    # Get the timeout for the complete test(s)
    timeout = get_timeout(config)
    
    # Get the watchdog timeout
    watchdog = get_watchdog(config)
    
    # Get the minor frame in major frame count
    majorframe = get_majorframe(config)
    
    # Get the configuration mode (i.e. realtime or not).
    realtime = get_realtime(config)
    
    # Get the reset terminal bool value (i.e. reset on exit or not).
    resetterm = get_resetterm(config)
    
    # Create an event handler for event callbacks
    my_event_handler = ArteEventHandler()
    
    # Create a server
    if not realtime:
        my_server = ArteServer("localhost", 9999, client_count, my_event_handler, timeouts, majorframe)
        logging.info('Running in faster than realtime mode')
    else:
        # TODO add realtime server
        my_server = ArteServer("localhost", 9999, 1, my_event_handler, timeouts, majorframe)
        logging.info('Running in realtime mode')

    # Create a test fixture
    my_test_fixture = ArteTestFixture("test1", config, my_event_handler)
    
    # Startup the clients
    my_event_handler.startup()
     
    # Wait on a shutdown event or timeout
    if my_event_handler.shutdown_notification.wait(timeout):
        # A shutdown request was received from a client.
        my_event_handler.shutdown()
        sys.exit(my_event_handler.returnCode)
    
    # The event wait returned false so a timeout was reached.
    # Shutdown the server.
    logging.error('Configured timeout reached %d seconds', timeout)

    # Terminate clients.
    my_event_handler.shutdown()

    # If configured, reset terminal before exit.
    if resetterm:
        # Reset the terminal 
        os.system("reset")

    # Exit with status 1
    sys.exit(1)

if __name__ == '__main__':
    main()
