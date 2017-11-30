# -*- coding: utf-8 -*-
from __future__ import unicode_literals
import unittest
from toolkit import *
from consumers import *
from views import *


# Create your tests here.



class Test_toolkit(unittest.TestCase):



    def test_directory_outputs(self):
        get_directory('')
        self.assertEquals(get_directory('')['path'], '')
        self.assertNotEqual(get_directory('/flight')['path'],'/flidfght')
        self.assertEquals(get_directory('/apps/cs')['path'], '/apps/cs')
        self.assertEquals(get_directory('/flight')['path'], '/flight')


    def test_directory_exeptions(self):

        self.assertRaises(OSError,get_directory, '/opt')
        self.assertRaises(OSError,get_directory,'/apps/cs/main.pug')
        self.assertRaises(OSError, get_directory, 'asda')
        self.assertRaises(AttributeError, get_directory, 54)


class Test_bitefy(unittest.TestCase):

    def test_bitefy_outputs(self):
        self.assertEquals(byteify(24), 24)
        self.assertEquals(byteify('hello'), 'hello')
        self.assertEquals(byteify({u'a':u'b'}), {'a':'b'})
        self.assertEquals(byteify(24), 24)

class Test_logging(unittest.TestCase):

    def numeric_inputs(self):
        self.assertEquals(log('1','2','3.32'),None)





if __name__ == '__main__':
    unittest.main()