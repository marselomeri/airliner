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
from arte_launcher import ArteSubprocess
import time
import sys
import logging

class ArteTestFixture(object):
    """A test fixture to handle test setup and teardown. 
    
    Note:
        The test fixture uses ArteLauncher to startup and terminate
            clients. The configuration file specifies the clients to be 
            included in setup and teardown. 

    Args:
        name (str): The name of the test fixture.
        config (:obj: deserialized JSON object): The deserialized JSON
            configuration file.
        event_handler (:obj: ArteEventHandler): An instance of an 
            ArteEventHandler object.

    Attributes:
        name (str): The name of the test fixture.
        config (:obj: deserialized JSON object): The deserialized JSON
            configuration file.
        event_handler (:obj: ArteEventHandler): An instance of an 
            ArteEventHandler object. Callbacks are assigned to the 
            test_setup and test_teardown EventHandler objects.
        timer (:obj: threading.Timer): The current threading.Timer 
            object.
        client_count (unsigned int): The number of clients in the 
            configuration file.
        clients (:obj:`list` of :obj:`ArteSubprocess`): A list of client
            subprocess objects.
        return_code (int): The return code of a terminated or killed 
            subprocess.
        
    """
    def __init__(self, name, config, event_handler):
        self.name = name
        self.config = config
        self.client_count = 0
        # register test setup and teardown with the event handler
        self.event_handler = event_handler
        self.event_handler.startup += self.test_setup
        self.event_handler.shutdown += self.test_teardown
        # count the number of clients in the config file.
        self.client_count = 0
        self.count_clients()
        self.clients = []
        self.return_code = None
        
    def count_clients(self):
        """Count the number of clients specified in the
            configuration file. Sets the client_count attribute.
        """
        for i in self.config['clients']:
            self.client_count += 1
            
    def test_setup(self, sender):
        """Launches all clients specified in the configuration file
            with the command, output path, and current working directory 
            to be used when launching the client.
        """
        # Loop through the client list
        for i in self.config['clients']:
            self.clients.append(ArteSubprocess(i['command'], i['output'], i['cwd']))

    def test_teardown(self, sender):
        """Terminates or kills all the clients in the client list.
        
        Note:
            test_teardown will first try to stop the client subprocess.
                stop_subprocess mimics subprocess terminate which sends 
                SIGTERM and if the process doesn't return anything after 
                0.1 seconds if then calls kill_subprocess (subprocess 
                kill) which sends SIGKILL.
            
        Args:
            sender (:obj:): The responsible object that executes the
                event handler.
        """
        # Loop through the client list
        for i in range(self.client_count):
            self.clients[i].stop_subprocess()
            time.sleep(0.1)
            self.returnCode = self.clients[i].poll_subprocess()
            logging.info('terminated client process returned %s ', str(self.returnCode))
            if self.returnCode == None:
                logging.error('client failed to terminate, attempting to kill')
                # poll returned None so the process hasn't terminated
                self.clients[i].kill_subprocess()
                time.sleep(0.1)
                self.returnCode = self.clients[i].poll_subprocess()
                logging.error('terminated client process returned %s ', str(self.returnCode))

