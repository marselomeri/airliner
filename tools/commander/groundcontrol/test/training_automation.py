import unittest
from selenium import webdriver
from selenium.webdriver.support.ui import Select
import requests
import time
import os
print os.getcwd()
from .. toolkit import get_directory

apps = []
fixApps = {}
totalApps = 0
validApps = 0

def freeClicks( list):
    for each in list:

        if each.find_element_by_tag_name('a').get_attribute('href') != 'http://localhost:8000/#':
            #ApplicationGUI.totalApps = ApplicationGUI.totalApps + 1
            slug = each.find_element_by_tag_name('a').get_attribute('href')
            try:
                res = requests.get(slug)
            except:
                pass
            if res.reason == 'OK':
                #ApplicationGUI.validApps = ApplicationGUI.validApps + 1
                apps.append(largen(slug))
            else:
                fixApps[largen(slug)] = {'code': res.status_code, 'err': res.reason}

            if list.index(each) == len(list) - 1:
                return
            else:
                continue

        lookup = each.find_element_by_tag_name('a').get_attribute('onclick')
        half_lookup = lookup.replace('getWorkspaceDir(\'', '').replace('\');', '')
        op = get_directory(half_lookup)
        #self.assertTrue(op['err'] == None)
        #self.assertTrue(tk.byteify(op['path']) == half_lookup)
        each.find_element_by_tag_name('a').click()

        time.sleep(0.2)
        ul = each.find_element_by_class_name('jarvis-menu-applied')
        ls = ul.find_elements_by_tag_name('li')
        freeClicks(ls)
        time.sleep(0.5)


def largen(self, link):
    parts = link.split(':8000')
    new_url = parts[0] + ':8000/#' + parts[1]
    return new_url


def nano(self, link):
    parts = link.split(':8000')
    return parts[1]


def clean_nano(self, link):
    parts = link.split(':8000/#/')
    slugs = parts[1].split('/')
    name = ''
    last = slugs[len(slugs) - 1].split('.')
    last = last[0]
    for each in slugs[:len(slugs) - 2]:
        name = name + '_' + str(each)
    name = name + '_' + last
    return name


def tlm_nano(self, link):
    parts = link.split(':8000')
    names = parts[1]

if __name__ == '__main__':
    driver = webdriver.Firefox()
    driver.get('http://localhost:8000')

    #-------automation-------
    #clicking on directories
    aside = driver.find_element_by_id('left-panel')
    navbox = aside.find_element_by_id('navBox')
    ul =  navbox.find_element_by_class_name('jarvis-menu-applied')
    list = ul.find_elements_by_tag_name('li')
    freeClicks(list)
    time.sleep(1)

    #------------------------


    driver.quit()