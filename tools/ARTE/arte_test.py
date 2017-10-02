from arte_launcher import arte_subprocess
import time
import sys

class test_fixture(object):
    def __init__(self, name, config):
        self.name = name
        self.config = config
        self.client_count = 0
        self.clients = []
        self.timeout = None

    # TODO make this __private
    def test_setup(self):
        # Loop through the client array
        for i in self.config['clients']:
            self.clients.append(arte_subprocess(i['command'], i['output']))
            self.client_count += 1

        self.timeout = self.config['timeout']

    # TODO make this __private
    def test_teardown(self):
        # Loop through the client array
        for i in range(self.client_count):
            self.clients[i].stop_subprocess()
            print ("terminated client process returned: ", str(self.clients[i].poll_subprocess()))

    def test_run(self):
        self.test_setup()
        # for now sleep duration timeout
        time.sleep(self.timeout)
        self.test_teardown()
        sys.exit(0)
