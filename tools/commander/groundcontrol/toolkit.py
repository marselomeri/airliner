import os,json
from websocket import create_connection
import datetime

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

data = [1,4,0,{"dt":"PARAMETER","data":{"parameter":[{"id":{"name":"/CFS/CFE_EVS/ErrCounter"},"rawValue":{"type":"UINT32","uint32Value":0},"engValue":{"type":"UINT32","uint32Value":0},"acquisitionTime":1509120382791,"generationTime":316989422671,"acquisitionStatus":"ACQUIRED","processingStatus":true,"acquisitionTimeUTC":"2017-10-27T16:05:45.791","generationTimeUTC":"1980-01-17T20:36:43.671","expirationTime":1509120384291,"expirationTimeUTC":"2017-10-27T16:05:47.291"}]}}]

def preprocessAtServer(d):
    if d[1] == 4:
        print 'GOT VALID DATA RESPONSE.'
        #for parameter in d[3]:








preprocessAtServer(data)