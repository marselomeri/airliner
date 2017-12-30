import unittest
from mock import patch
from channels import Channel
from channels.tests import ChannelTestCase,apply_routes,HttpClient
from channels import route, Group
from groundcontrol.consumers import *

import django
import os
os.environ.setdefault('YAMCS_WORKSPACE', '/home/vagrant/git/airliner/config/shared/commander_workspace/') + 'web'
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "commander.settings")
django.setup()

#settings.configure()

class ConsumerTests(ChannelTestCase):
    @patch('groundcontrol.consumers.Telemetry.connect', return_value=9)
    def test_example(self,connect):
        #tlm = Telemetry()
        print connect()
        client = HttpClient()
        client.send_and_consume('websocket.connect', text='INVOKE', path='/inst')
        print client.receive()

if __name__ == '__main__':
    Toolkit = unittest.TestLoader().loadTestsFromTestCase(ConsumerTests)
    Suite = unittest.TestSuite([Toolkit])
    unittest.TextTestRunner(verbosity=2).run(Suite)