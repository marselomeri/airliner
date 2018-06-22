"""This file comprises custom functions which support consumers.py and other python code.
which is why it is called toolkit.
"""

import os,json
import datetime
import ast
import re
import redis
import sqlite3

## Global variables

## Register working_dir
#try:
working_dir = os.getenv('YAMCS_WORKSPACE', '/home/vagrant/git/airliner/config/shared/commander_workspace/') + 'web'

#os.environ['YAMCS_WORKSPACE']+'web'
#except:
    #working_dir = '/home/vagrant/git/airliner/config/shared/commander_workspace/web'
    #pass

## Register redis caching server
r = redis.StrictRedis(host='localhost', port=6379, db=0)

## Custom Functions/Methods

def getDate():
    """!
    Get current datetime.
    @return: String
    """
    return str(datetime.datetime.now())

def get_directory(path):
    """!
    Program scrapes file system to return sub-directories and files underlying path.
    @param path: file or directory
    @return: JSON object with current path, error message if any, and sub-directories and files as nested JSON.
    """
    outFiles=[]
    error= None
    try:
        #print '//*/*/*/*/*/*/*/*/**/*/*/*/*/*',working_dir
        rootdir = path.rstrip(os.sep)
        rootdir = working_dir +  path

        for e in os.listdir(rootdir):
            absolutePath = str(rootdir+'/'+e)
            urlPath =absolutePath.replace(working_dir,'')
            type = 'unknown'
            if os.path.isdir(absolutePath):
                type = 'dir'
            elif os.path.isfile(absolutePath):
                type = 'file'
            entry = {'absolute_path': absolutePath,'path':urlPath,'name':e,'type':type}
            outFiles.append(entry)
            outFiles.sort()
    except IOError:
        error=IOError
        pass
    return {'err':error,'path':path,'files': outFiles}

def byteify(input):
    """!
    Cleans dictionaries and lists of unicode.
    @param input: list or dictionary
    @return: Clean dictionary or list
    """
    if isinstance(input, dict):
        return {byteify(key): byteify(value)
                ## python 2.7 only (x.iteritems())
                for key, value in input.iteritems()}
    elif isinstance(input, list):
        return [byteify(element) for element in input]
    elif isinstance(input, unicode):
        return input.encode('utf-8')
    else:
        return input


def log(name,status,status_type):
    """!
    A substitute for a print statement with predefined formatting
    @param name: name your log entry
    @param status: a message
    @param status_type: classify your log entry among (INFO, DEBUG, ERROR) types
    @return: Void
    """
    date = getDate()
    print str(date)+' - '+str(status_type)+' - '+str(status)+' ( NAME : '+str(name)+' )'



def preProcess(d):
    """!
    Processes only certain strings, this is to compensate for the syntax differences between javascript and python code.
    @param d: text
    @return: processed text
    """
    array_obj = []
    dealing_with_incompat = re.sub(r"\btrue\b", "True", d)
    if len(dealing_with_incompat)>0:
        array_obj = ast.literal_eval(dealing_with_incompat)
    else:
        raise IOError
    if array_obj[1] == 4:
        x = array_obj[3]["data"]
        x1 = x['parameter']
        for i in range(len(x1)):
            if r.get('instance')=='None':
                x['parameter'][i]['instance']=r.get('default_instance')
            else:
                x['parameter'][i]['instance'] = r.get('instance')
        return str(x)


def collectTestCases(conn,mapper,input,eo,desc):
    """!
    performs insert in a data base given the database connection passed in and parameter.
    @param conn: sql connection to `test-database`
    @param mapper: a user defined string, categorizes various database entries.
    @param input: a string object before a certain process is applied on it.
    @param eo: a string object after the process is applied on it.
    @param desc: description of the process that is applied on the input.
    @return: Void
    """
    c = conn.cursor()
    insert = 'INSERT INTO `TESTCASES`(`mapping`,`input`,`output`,`time_stamp`,`description`)  VALUES (?,?,?,?,?)'
    c.execute(insert,(mapper,input,eo,getDate(),desc))


def readJsonFromCloseCirlce(closecircle):
    with open(working_dir+'/'+closecircle+'/jsondata.json') as jfile:
        data = json.load(jfile)
    return data