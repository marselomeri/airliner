import os,json
from websocket import create_connection
import datetime
import ast
import re

try:
    working_dir = os.environ['YAMCS_WORKSPACE']+'web'
except:
    working_dir ='/home/vagrant/git/airliner/config/shared/commander_workspace/web'

#TOOLS
def getDate():
    return str(datetime.datetime.now())

def get_directory_structure(rootdir):
    dir = {}
    rootdir = rootdir.rstrip(os.sep)
    start = rootdir.rfind(os.sep) + 1
    for path, dirs, files in os.walk(rootdir):
        folders = path[start:].split(os.sep)
        subdir = dict.fromkeys(files)
        parent = reduce(dict.get, folders[:-1], dir)
        parent[folders[-1]] = subdir
    return dir


def get_directory(path):

    outFiles=[]
    error= None
    try:
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

    except IOError:
        error=IOError
        pass


    return {'err':error,'path':path,'files': outFiles}

def byteify(input):
    if isinstance(input, dict):
        return {byteify(key): byteify(value)
                for key, value in input.iteritems()}
    elif isinstance(input, list):
        return [byteify(element) for element in input]
    elif isinstance(input, unicode):
        return input.encode('utf-8')
    else:
        return input


def log(name,status,status_type):
    date = getDate()
    print str(date)+' - '+str(status_type)+' - '+str(status)+' ( NAME : '+str(name)+' )'


def preProcess(d):
        dealing_with_incompat = re.sub(r"\btrue\b", "True", d)
        array_obj = ast.literal_eval(dealing_with_incompat)
        if array_obj[1] == 4:
            x = array_obj[3]["data"]
            x1 = x['parameter']
            for i in range(len(x1)):
                x['parameter'][i]['instance']='softsim'
            return str(x)



def readSESSION():
    with open('/home/vagrant/git/airliner/tools/commander/groundcontrol/session.json') as json_data:
        d = json.load(json_data)
        json_data.close()
        return d

def writeSESSION(j):
    with open('/home/vagrant/git/airliner/tools/commander/groundcontrol/session.json', 'w') as f:
        json.dump(j, f)
