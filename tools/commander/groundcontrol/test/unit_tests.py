import unittest
from mock import patch
from channels.tests import ChannelTestCase, apply_routes
from channels.tests.http import HttpClient
from django.contrib.auth import get_user_model

from commander.routing import channel_routing


import django
import os
os.environ.setdefault('YAMCS_WORKSPACE', '/home/vagrant/git/airliner/config/shared/commander_workspace/') + 'web'
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "commander.settings")
django.setup()

#settings.configure()

@apply_routes([channel_routing])
class ConsumerTests(ChannelTestCase):

    #@patch('groundcontrol.consumers.Telemetry.connect', return_value=9)


    def test_example(self):
        client = HttpClient()
        client.send_and_consume(u'websocket.receive', content = {"order":1},text='kill_tlm' ,path='/tlm_s')
        print client.receive()
        #self.assertEqual(client.receive(), {'text':'Hello'})
        #self.assertFalse(client.receive())  # check that is nothing to receive












if __name__ == '__main__':
    Toolkit = unittest.TestLoader().loadTestsFromTestCase(ConsumerTests)
    Suite = unittest.TestSuite([Toolkit])
    unittest.TextTestRunner(verbosity=2).run(Suite)