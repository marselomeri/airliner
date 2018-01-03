import unittest
from mock import patch
from channels.tests import ChannelTestCase, apply_routes
from channels.tests.http import HttpClient
from commander.routing import channel_routing
from groundcontrol.consumers import *
import django
import os
import socket
import sys
import time
import mock_YAMCS as tstserv

os.environ.setdefault('YAMCS_WORKSPACE', '/home/vagrant/git/airliner/config/shared/commander_workspace/') + 'web'
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "commander.settings")
django.setup()
#settings.configure()


HOST = 'localhost'
PORT = 8090


@apply_routes([channel_routing])
class ConsumerTests(ChannelTestCase):
    #@patch('groundcontrol.consumers.Telemetry.connect', return_value=9)
    def setUp(self):
        self.client = HttpClient()
        tstserv.start()

    def tearDown(self):
        #time.sleep(1)
        tstserv.kill()



    def test_connection_to_telemetry(self):
        self.client.send_and_consume(u'websocket.connect',text='test',path='/tlm')
        self.assertEqual(self.client.receive(), 'OK', msg='Telemetry connection failed.')
        self.assertFalse(self.client.receive(), msg='No other message shoulg be received.')

    def test_subscribtion_request(self):
        self.client.send_and_consume(u'websocket.receive',text={'tlm':[{'name':'/CFS/DS/CmdAcceptedCounter'}]},path='/tlm')
        self.assertTrue(len(sock_map)>0 and len(sock_map)<=1, msg = 'should have only 1 item in the dictionary')
        self.assertTrue(len(proc_map) > 0 and len(proc_map) <= 1, msg = 'should have only 1 item in the dictionary')
        print sock_map
        print proc_map
        self.client.send_and_consume(u'websocket.receive', text={'tlm': [{'name': '/CFS/DS/CmdAcceptedCounter kill_tlm'}]},path='/tlm')
        self.assertTrue(len(sock_map) > 0 and len(sock_map) <= 1, msg='should have only 1 item in the dictionary')
        self.assertTrue(len(proc_map) > 0 and len(proc_map) <= 1, msg='should have only 1 item in the dictionary')
        print sock_map
        print proc_map
        time.sleep(1)
        self.client.send_and_consume(u'websocket.receive', text='USALL', path='/tlm')
        self.assertTrue(len(sock_map) <= 0, msg='should have only 0 item in the dictionary')
        self.assertTrue(len(proc_map) <= 0, msg='should have only 0 item in the dictionary')
        print sock_map
        print proc_map




if __name__ == '__main__':
    Toolkit = unittest.TestLoader().loadTestsFromTestCase(ConsumerTests)
    Suite = unittest.TestSuite([Toolkit])
    unittest.TextTestRunner(verbosity=2).run(Suite)