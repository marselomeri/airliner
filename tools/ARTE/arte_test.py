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

class ArteTestFixture(object):
    def __init__(self, name, config, event_handler):
        self.name = name
        self.config = config
        self.client_count = 0
        # register test setup and teardown with the event handler
        self.event_handler = event_handler
        self.event_handler.startup += self.test_setup
        self.event_handler.shutdown += self.test_teardown
        # count the number of clients in the config file.
        self.count_clients()
        self.clients = []
        self.timeout = None
        self.return_code = None
        
    def count_clients(self):
        for i in self.config['clients']:
            self.client_count += 1

    def test_setup(self, sender):
        # Loop through the client array
        for i in self.config['clients']:
            self.clients.append(ArteSubprocess(i['command'], i['output'], i['cwd']))
        self.timeout = self.config['timeout']

    def test_teardown(self, sender):
        # Loop through the client array
        for i in range(self.client_count):
            self.clients[i].stop_subprocess()
            time.sleep(1)
            self.returnCode = self.clients[i].poll_subprocess()
            print ("terminated client process returned: ", str(self.returnCode))
            if self.returnCode == None:
                print("client failed to terminate, attempting to kill")
                # poll returned None so the process hasn't terminated
                self.clients[i].kill_subprocess()
                time.sleep(1)
                self.returnCode = self.clients[i].poll_subprocess()
                print ("killed client process returned: ", str(self.returnCode))

