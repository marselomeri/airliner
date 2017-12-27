import unittest
from selenium import webdriver
from selenium.webdriver.support.ui import Select
import requests
import time
from .. import toolkit as tk
import unicodedata
import redis
from pprint import pprint
from multiprocessing import Process


class ApplicationGUI(unittest.TestCase):



    @classmethod
    def setUpClass(cls):
        cls._r = redis.StrictRedis(host='localhost', port=6379, db=0)
        cls._db_path = cls._r.get('app_path')
        cls.driver = webdriver.Firefox()
        cls.arr = ['apps','cfe','common','flight','mpu9250','probe','scripts']
        cls.apps = []
        cls.fixApps = {}
        cls.totalApps = 0
        cls.validApps = 0
        cls.driver.get('http://localhost:8000')

    @classmethod
    def tearDownClass(cls):
        cls.driver.quit()

    #@unittest.skip("demonstrating skipping")
    def test_A_hosting(self):


        title = unicodedata.normalize("NFKD", self.driver.title)
        self.assertEqual(title,'flight  /  pilot.jade')
        time.sleep(2)

    #@unittest.skip("demonstrating skipping")
    def test_B_directory_listing_superficial(self):
        aside = self.driver.find_element_by_id('left-panel')
        navbox = aside.find_element_by_id('navBox')
        ul =  navbox.find_element_by_class_name('jarvis-menu-applied')
        list = ul.find_elements_by_tag_name('a')
        for each in list:
            span = each.find_element_by_tag_name('span')
            #print span
            self.assertTrue(span.text in self.arr)

    #@unittest.skip("demonstrating skipping")
    def test_C_recursive_clicks_on_applications(self):
        aside = self.driver.find_element_by_id('left-panel')
        navbox = aside.find_element_by_id('navBox')
        ul =  navbox.find_element_by_class_name('jarvis-menu-applied')
        list = ul.find_elements_by_tag_name('li')
        #clickers = list
        self.freeClicks(list)
        time.sleep(1)

    def freeClicks(self,list):

        for each in list:

            if  each.find_element_by_tag_name('a').get_attribute('href')!='http://localhost:8000/#':
                ApplicationGUI.totalApps = ApplicationGUI.totalApps +  1
                slug = each.find_element_by_tag_name('a').get_attribute('href')
                try:
                    res = requests.get(slug)
                except:
                    pass
                if res.reason == 'OK' :
                    ApplicationGUI.validApps = ApplicationGUI.validApps + 1
                    self.apps.append(self.largen(slug))
                else:
                    self.fixApps[self.largen(slug)] = {'code':res.status_code,'err':res.reason}

                if list.index(each) == len(list)-1:
                    return
                else:
                    continue

            lookup = each.find_element_by_tag_name('a').get_attribute('onclick')
            half_lookup = lookup.replace('getWorkspaceDir(\'', '').replace('\');','')
            op = tk.get_directory(half_lookup)
            self.assertTrue(op['err']==None)
            self.assertTrue(tk.byteify(op['path'])==half_lookup)
            each.find_element_by_tag_name('a').click()

            time.sleep(0.2)
            ul = each.find_element_by_class_name('jarvis-menu-applied')
            ls = ul.find_elements_by_tag_name('li')
            self.freeClicks(ls)
            time.sleep(0.5)

    #@unittest.skip("demonstrating skipping")
    def test_D_instance_in_list(self):
        time.sleep(1)
        yis = self.driver.find_element_by_id('yamcs-instance-selected')
        self.assertTrue(yis.text=='Select')
        yis.click()
        ul = self.driver.find_element_by_id('yamcs-instance-list')
        a = ul.find_elements_by_tag_name('a')
        name_list = []
        for each in a:
            name_list.append(each.text)
        self.assertTrue('softsim' in name_list)


    def largen(self,link):
            parts = link.split(':8000')
            new_url = parts[0]+':8000/#'+parts[1]
            return new_url

    def nano(self,link):
        parts = link.split(':8000')
        return parts[1]

    def clean_nano(self,link):
        parts = link.split(':8000/#/')
        slugs = parts[1].split('/')
        name =''
        last = slugs[len(slugs)-1].split('.')
        last = last[0]
        for each in slugs[:len(slugs)-2]:
            name = name +'_'+str(each)
        name = name +'_'+last
        return name

    def tlm_nano(self,link):
        parts = link.split(':8000')
        names = parts[1]

    #@unittest.skip("demonstrating skipping")
    def test_E_select_instance(self):
        ul = self.driver.find_element_by_id('yamcs-instance-list')
        a = ul.find_elements_by_tag_name('a')

        for each in a:
            if each.text == 'softsim':
                each.click()
                break
        yis = self.driver.find_element_by_id('yamcs-instance-selected')
        self.assertTrue(yis.text == 'softsim')
        time.sleep(5)
        self.driver.implicitly_wait(3)

    def test_F_application_binding(self):
        c = 0
        yis = self.driver.find_element_by_id('yamcs-instance-selected')
        if yis.text == 'softsim':
            for each in self.apps:
                name = self.clean_nano(each)
                self.driver.get(each)
                time.sleep(3)
                tlm_elements = self.driver.find_elements_by_xpath('//span[@data-sage]')
                dash_count = 0
                dash_value = False
                for te in tlm_elements:
                    #no telementry found for one item
                    if tk.byteify(te.text) =='---':
                        dash_count = dash_count+1
                #invalid app
                if dash_count == len(tlm_elements):
                    self.apps.remove(each)
                    ApplicationGUI.validApps = ApplicationGUI.validApps -1
                    continue
                else:
                    #ALL ITEMS VERIFY
                    for tlm_element in tlm_elements:
                        self.assertTrue(tk.byteify(tlm_element.text) != '---')
                    #BUTTON-EVENTS
                    EC = self.get_event_count()
                    cmd_elements = self.driver.find_elements_by_xpath('//button[@data-sage]')
                    total_btns = len(cmd_elements)
                    good_btn = 0
                    bad_btn = 0
                    #print 'TOTALBTN # ', total_btns
                    OK = self.driver.find_elements_by_xpath('//button[@class=\'btn btn-primary\' and @type=\'button\']')
                    for button in cmd_elements[0:2]:
                        button.click()
                self.assertTrue(self.get_event_count()>EC)
            #self.print_resources()

    @unittest.skip("demonstrating skipping")
    def get_event_count(self):
        return int(self.driver.find_element_by_xpath('//b[@id=\'EventCount\']').text)

    def print_resources(self):
        print 'TOTAL APPS #  ',ApplicationGUI.totalApps
        print 'VALID APPS #  ',ApplicationGUI.validApps

    #def test_G_verify_telemetry(self):


if __name__ == '__main__':
    GUI = unittest.TestLoader().loadTestsFromTestCase(ApplicationGUI)


    Suite = unittest.TestSuite([GUI])

    slack = '\n\nRunning GUI - Tests for Commander....\n\n'
    print slack
    unittest.TextTestRunner(verbosity=2).run(Suite)




