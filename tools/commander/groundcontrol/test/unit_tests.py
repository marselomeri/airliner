import unittest
from mock import patch
from channels import Channel
from channels.tests import ChannelTestCase,apply_routes,HttpClient
from channels.routing import route_class
from channels import route, Group
from groundcontrol.consumers import *

import django
import os
os.environ.setdefault('YAMCS_WORKSPACE', '/home/vagrant/git/airliner/config/shared/commander_workspace/') + 'web'
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "commander.settings")
django.setup()

#settings.configure()












if __name__ == '__main__':
    Toolkit = unittest.TestLoader().loadTestsFromTestCase(ConsumerTests)
    Suite = unittest.TestSuite([Toolkit])
    unittest.TextTestRunner(verbosity=2).run(Suite)