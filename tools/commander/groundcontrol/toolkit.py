import os,json
import datetime
import ast
import re
import redis

try:
    working_dir = os.environ['YAMCS_WORKSPACE']+'web'
except:
    working_dir = '/home/vagrant/git/airliner/config/shared/commander_workspace/web'
r = redis.StrictRedis(host='localhost', port=6379, db=0)
###########TOOLS###########




#DEBUG
def getDate():
    return str(datetime.datetime.now())

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
            outFiles.sort()

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
                if r.get('instance')==None:
                    x['parameter'][i]['instance']=r.get('default_instance')
                else:
                    x['parameter'][i]['instance'] = r.get('instance')
            return str(x)

#DEBUG
def introspectResult(d):
    the_d = json.loads(d)
    tlm_data = the_d[3]['data']
    tlm_list = tlm_data['parameter']
    for e in tlm_list:
        to_print = e['id']['name']
        print getDate(),'  ',to_print