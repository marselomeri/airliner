"""Consumer.py is the final destination of all websocket routing that happens in django. Each incoming message is picked
up by one of the several workers and gets routed to respective function call in this file. The worker executes the function
passing the message as parameter. The response is written in the received message itself and put back on the channel/socket.
"""

## swiss-knife
import toolkit as tk
import urllib,json,os,psutil,requests,time,socket,base64,ast
from channels import Group
from websocket import create_connection
from multiprocessing import Process
## datastores
import redis,sqlite3


redis_cache = redis.StrictRedis(host='localhost', port=6379, db=0)## Initialize redis caching database



print '***********',redis_cache
mode = 2#int(redis_cache.get('mode'))## Initialize mode defined in launch_config.json
test_db_path = redis_cache.get('app_path')## Initialize test database path defined in launch_config.json
number_of_workers = redis_cache.get('number_of_workers')## Initialize number or parallel workers defined in launch_config.json
defaultInstance= redis_cache.get('instance')## Initialize default instance defined in launch_config.json
address = redis_cache.get('address')## Initialize address to pyliner/yamcs defined in launch_config.json
port = redis_cache.get('port')## Initialize port to pyliner/yamcs defined in launch_config.json
sock_map = {}## A dictionary to store websockets which connect backend, mapped with unique id in message object.
proc_map = {}## A dictionary to store processes which push telemetry to frontend, mapped with unique id in message object.
test_sampling_frequency = (1.0/10)## The number of samples collected everytime the `push` function yields data
sock_map_e = {}## A dictionary to store websockets which connect backend, mapped with unique id in message object.
proc_map_e = {}## A dictionary to store processes which push telemetry to frontend, mapped with unique id in message object.
video_socket = None## An empty variable which will be later used to store the video-udp socket object.
video_port = int(redis_cache.get('video_port'))## Initialize video port to pyliner/yamcs defined in launch_config.json.



def tlm_connect( message):
    """!
    Accepts request and establishes a connection with client.
    @param message: connection request from client, this message will connection headers.
    @return: void
    """

    Group('tlm_bc').add(message.reply_channel)
    Feedback = json.dumps("OK")
    message.reply_channel.send({'accept': True, 'text':Feedback})
    tk.log('Instance', 'Connected.', 'INFO')

def tlm_disconnect( message):
    """!
    Accepts disconnection message and disconnects with client.
    @param message: disconnection request from client, this message will disconnection headers.
    @return: void
    """
    Feedback = json.dumps("ENDOK")
    message.reply_channel.send({'close': True, 'text':Feedback})
    Group('tlm_bc').discard(message.reply_channel)
    tk.log('Instance', '(Dis)connected.', 'INFO')



def getTelemetry( message):
    """!
    Takes the telemetry message object and either sends a subscribe or unsubscribe signal to pyliner/yamcs.
    Creates or destroys `push` processes based on signal received.
    @param message: telemetry message object is sent from the client.
    @return: void
    """
    message_client_id = message.content['reply_channel']
    ## clean text
    message_text = tk.byteify(message.content['text'])
    ## unsubscribe signal
    if message_text.find('kill_tlm') != -1:
        try:
            msg = message_text.replace('kill_tlm', '')
            msg_text_obj = json.loads(msg)
            temp = ' {"parameter":"unsubscribe", "data":{"list":' + str(tk.byteify(msg_text_obj['tlm'])) + '}}'
            temp = temp.replace("\'", "\"")
            to_send = '[1,1,0,' + str(temp) + ']'
            ## Train
            test_db_wrapper(message_text,'null','KILTLM','unsubscribe telemetry')
            ## sending unsubscribe signal to pyliner/yamcs
            sock_map[message_client_id].send(to_send)
            tk.log('Instance', '[UNSUBSCRIBED] - '+message_client_id+' - '+msg, 'DEBUG')
        except:
            ## TODO: safely log error, unit test required
            tk.log('Instance', '[ERR - UNSUBSCRIBED] - ' + message_client_id + ' - ' + message_text, 'ERROR')
            pass
    ## kill all processes
    elif message_text.find('USALL')!=-1:
        try:
            to_kill_pid = proc_map[message_client_id]
            to_kill = psutil.Process(to_kill_pid)
            to_kill.kill()
            del proc_map[message_client_id]
            del sock_map[message_client_id]
            tk.log('Instance', '[KILLED] - ' + str(to_kill_pid), 'DEBUG')

        except:
            ## TODO: safely log error, unit test required
            tk.log('Instance', '[ERR - KILLED] - NA', 'ERROR')
            pass
    ## Subscribe signal
    ## Send message, start a system process, store current data in a local dict.
    elif message_text.find('tlm')!=-1:
        msg_text_obj = json.loads(message_text)
        temp = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(msg_text_obj['tlm'])) + '}}'
        temp = temp.replace("\'", "\"")
        to_send = '[1,1,0,' + str(temp) + ']'
        ## Train
        test_db_wrapper(message_text, 'null', 'SUBTLM', 'subscribe telemetry')
        ## One time per application cycle.
        if message_client_id not in sock_map.keys():
            try:
                client_id = message.content['reply_channel']
                #print client_id
                #ws = create_connection('ws://' + str(address) + ':' + str(port) + '/' + redis_cache.get('instance') + '/_websocket')
                ws = create_connection('ws://127.0.0.1:8090/softsim/_websocket')

                #print ws
                sock_map[client_id] = ws
                #msg_map[message_client_id] = message
                sock_map[message_client_id].send(to_send)



                #print client_id
                #print sock_map
                #Feedback = json.dumps("OK")
                #message.reply_channel.send({'text': Feedback})
                process = Process(target=push1,args=(sock_map[message_client_id],))
                process.start()
                proc_map[client_id] = process.pid
                tk.log('Instance', '[PROCESS] - ' + str(process.pid) , 'DEBUG')
            except Exception as e:
                ## TODO: safely log error, unit test required
                tk.log('Instance', '[ERR - PROCESS] - '+str(e)+' -  ' + message_client_id + ' - ' + message_text, 'ERROR')
                pass
        ## If already a socket is created then continue and use that socket
        else:
            try:
                sock_map[message_client_id].send(to_send)
                tk.log('Instance', '[SUBSCRIBED] - ' + message_client_id + ' - ' + message_text, 'DEBUG')
            except:
                ## TODO: safely log error, unit test required
                tk.log('Instance', '[ERR - SUBSCRIBED] - ' + message_client_id + ' - ' + message_text, 'DEBUG')
                pass

def push1( websocket_obj):
    """!
    A non-busy forever loop pushes telemetry to client.
    @param websocket_obj:  websocket object
    @return: void
    """
    freq_count = 1
    while True:
        #try:
            result = websocket_obj.recv()
            ## If result is not a ACK signal, in YAMCS case ACK looks like `[1,2,x]`
            if result != '[1,2,0]' :
                result2 = tk.preProcess(result)
                """INTROSPECTION PURPOSE ONLY"""
                e_list =  json.loads(json.dumps(ast.literal_eval(result2)))
                #for e in e_list['parameter']:
                #    print '-------------------',e['id']['name']
                #"""
                ## gets telemetry once every 10 loops
                if test_sampling_frequency*freq_count == 1 :
                    ## Train
                    test_db_wrapper(result, result2, 'PREPROCTLM', 'preprocess telemetry before sending')
                    freq_count = 1
                freq_count+=1
                try:
                    #message.reply_channel.send({'text': result2})
                    Group('tlm_bc').send({'text': result2})
                    #print result2
                except:
                    time.sleep(1)
                    #message.reply_channel.send({'text': result2})
                    Group('tlm_bc').send({'text': result2})
        #except Exception as e:
            #tk.log('Instance', 'Not able to push messages to client. Process killed. Error = '+str(e), 'ERROR')
            #break
        ## avoids busy-while-loop
        #time.sleep(0.01)



def cmd1_connect( message):
    """!
    Accepts request and establishes a connection with client.
    @param message: connection request from client, this message will connection headers.
    @return: void
    """
    Feedback = json.dumps("OK")
    message.reply_channel.send({'accept': True, 'text':Feedback})
    tk.log(defaultInstance,'Commanding connected to  client','INFO')

def cmd1_disconnect( message):
    """!
    Accepts disconnection message and disconnects with client.
    @param message: disconnection request from client, this message will disconnection headers.
    @return: void
    """
    Feedback = json.dumps("ENDOK")
    message.reply_channel.send({'close': True, 'text':Feedback})
    tk.log('defaultInstance', 'Commanding (dis)connected from client', 'INFO')

def cmd2_connect( message):
    """!
    Accepts request and establishes a connection with client.
    @param message: connection request from client, this message will connection headers.
    @return: void
    """
    Feedback = json.dumps("OK")
    message.reply_channel.send({'accept': True, 'text': Feedback})
    tk.log(defaultInstance,'Commanding connected to  client','INFO')

def cmd2_disconnect( message):
    """!
    Accepts disconnection message and disconnects with client.
    @param message: disconnection request from client, this message will disconnection headers.
    @return: void
    """
    Feedback = json.dumps("ENDOK")
    message.reply_channel.send({'close': True, 'text': Feedback})
    tk.log('defaultInstance', 'Commanding (dis)connected from client', 'INFO')

def test_db_wrapper(input,output,code,desc):
    """!
    This is a hook to record inputs and subsequent outputs that are generated by Command.
    @param input: a string object before a certain process is applied on it.
    @param output: a string object after the process is applied on it.
    @param code: a user defined string, categorizes various database entries.
    @param desc: description of the process that is applied on the input.
    @return: void
    """
    if mode == 0:
        try:
            conn = sqlite3.connect(test_db_path + '/test_database', timeout=5)
            tk.collectTestCases(conn, code, input, output, desc)
            conn.commit()
            conn.close()
            tk.log('Train', 'Item inserted in database.', 'DEBUG')
        except:
            ## TODO: safely log error, unit test required
            tk.log('Train', 'NA', 'ERROR')
            pass

def getCommandInfo( message):
    """!
    Takes the command message object and requests commanding information from pyliner/yamcs.
    @param message: command message object is sent from the client.
    @return: void
    """
    message_text = message.content['text']
    ## got handshake
    if message_text == 'HS':
        message.reply_channel.send({'text': 'HSOK'})
    ## got command object
    else:
        if defaultInstance!='None':
            response = urllib.urlopen('http://' + str(address) + ':' + str(port) + '/api/mdb/'+ str(defaultInstance)+'/commands'+message_text)
        else:
            response = urllib.urlopen('http://' + str(address) + ':' + str(port) + '/api/mdb/'+ redis_cache.get('default_instance')+'/commands'+message_text)
        data = json.loads(json.dumps(response.read()))
        data = data.replace("\"", "\'")
        ## Train
        test_db_wrapper(message_text, data, 'CMDINFO', 'commanding information')
        message.reply_channel.send({'text':data})

def postCommand( message):
    """!
    Takes the command message object and posts it to pyliner/yamcs.
    @param message: command message object is sent from the client.
    @return: void
    """
    message_text = message.content['text']
    to_post = json.loads(message_text)
    url=''
    if defaultInstance!='None':
        url = 'http://' + str(address) + ':' + str(port) +'/api/processors/' + str(defaultInstance) + '/realtime/commands' + to_post['name'] + '?nolink'
    else:
        url = 'http://' + str(address) + ':' + str(port) +'/api/processors/' + redis_cache.get('default_instance') + '/realtime/commands' + to_post['name'] + '?nolink'
    ## preparing post header
    msg = '{"sequenceNumber": 0,"origin": "user@my-machine","assignment":'+ str(json.dumps(to_post['args']))+',"dryRun": false}'
    headers = {
        'Content-Type': 'application/json',
        'Accept': 'application/json'
    }
    r = requests.post(url=url, data=msg, headers = headers)
    ## Train
    test_db_wrapper(message_text, r.status_code, 'CMDPOST', 'sending commands')
    got = r.text
    redis_cache.set('t_btn_cnt',str((int(redis_cache.get('t_btn_cnt'))+1)))
    op = json.dumps({"cmd":got,"code":r.status_code})
    message.reply_channel.send({'text': op})




def inst_connect( message):
    """!
    Accepts request and establishes a connection with client.
    @param message: connection request from client, this message will connection headers.
    @return: void
    """
    message.reply_channel.send({'accept': True})


def inst_disconnect( message):
    """!
    Accepts disconnection message and disconnects with client.
    @param message: disconnection request from client, this message will disconnection headers.
    @return: void
    """
    message.reply_channel.send({'close': True})


def tid_connect( message):
    """!
    Accepts request and establishes a connection with client.
    @param message: connection request from client, this message will connection headers.
    @return: void
    """
    message.reply_channel.send({'accept': True})


def tid_disconnect( message):
    """!
    Accepts disconnection message and disconnects with client.
    @param message: disconnection request from client, this message will disconnection headers.
    @return: void
    """
    message.reply_channel.send({'close': True})

def getInstanceList( message):
    """!
    This function is invoked by the client. Upon such an event, an instance list is requested from
    pyliner/yamcs which is forwarded to client.
    @param message: invoke signal sent from client
    @return: void
    """
    name = message.content['text']
    response = urllib.urlopen('http://' + str(address) + ':' + str(port) + '/api/instances')
    data = json.loads(json.dumps(response.read()))
    message.reply_channel.send({'text': data})


def setDefaultInstance(message):
    """!
    Upon an instance being selected on the application, this method is called; which updates redis cache
    whith the latest instance.
    @param message: message contains active instance name.
    @return: void
    """
    name = message.content['text']
    defaultInstance = name
    redis_cache.set('instance',name)









def dir_connect(message):
    """!
    Accepts request and establishes a connection with client.
    @param message: connection request from client, this message will connection headers.
    @return: void
    """
    message.reply_channel.send({'accept': True})

def dir_disconnect(message):
    """!
    Accepts disconnection message and disconnects with client.
    @param message: disconnection request from client, this message will disconnection headers.
    @return: void
    """
    message.reply_channel.send({'close': True})




def directoryListing(message):
    """!
    Takes the file or directory name in the  message object, scrapes file system and sends out a json to client
    which has sub-directories listed.
    @param message: message object with directory or file name is sent from the client.
    @return: void
    """
    name = message.content['text']

    response = tk.get_directory(name)
    data = json.dumps(response)
    ## Train
    test_db_wrapper(name, data,'DIR','obtain directory listing')
    message.reply_channel.send({'text': data})
    tk.log('Directory',' Packet ' + name + ' sent.','INFO')







def eve_connect(message):
    """!
    Accepts request and establishes a connection with client.
    @param message: connection request from client, this message will connection headers.
    @return: void
    """
    message.reply_channel.send({'accept': True})

def eve_disconnect(message):
    """!
    Accepts disconnection message and disconnects with client.
    @param message: disconnection request from client, this message will disconnection headers.
    @return: void
    """
    message.reply_channel.send({'close': True})

def getEvents(message):
    """!
    Upon receipt of invoke signal this function generates a process which pushes live event feeds to client.
    Upon receipt of kill signal the fucntion will kill the running process.
    @param message: event message object is sent from the client.
    @return: void
    """
    message_text = message.content['text']
    client_id = message.content['reply_channel']
    ## when invoke signal is received
    if message_text == 'INVOKE':
        data = '[1, 1, 1, {"events": "subscribe"}]'
        ws = None
        if defaultInstance == 'None':
            ws = create_connection('ws://' + address + ':' + str(port) + '/'+redis_cache.get('default_instance')+'/_websocket')
        else:
            ws = create_connection('ws://' + address + ':' + str(port) + '/'+defaultInstance+'/_websocket')
        ws.send(data)
        t = Process(target=push, args=(ws, message))
        t.start()
        proc_map_e[client_id] = t.pid
        sock_map_e[client_id] = ws

    # when kill signal is received
    elif message_text =='KILLSWITCH':
        try:
            us_sock = sock_map_e[client_id]
            data = '[1, 1, 1, {"events": "unsubscribe"}]'
            us_sock.send(data)
            tk.log('Event', '[UNSIBSCRIBED] - ' + client_id+' events', 'DEBUG')
        except:
            ## TODO: safely log error, unit test required
            tk.log('Event','Unable to unsubscribe.','ERROR')
            pass
        try:
            to_kill_pid = proc_map_e[client_id]
            print '****', to_kill_pid, proc_map_e
            to_kill = psutil.Process(to_kill_pid)
            to_kill.kill()
            tk.log('Event', '[KILLED] - ' + to_kill_pid, 'DEBUG')
        except:
            ## TODO: safely log error, unit test required
            tk.log('Event', 'Unable to kill.', 'ERROR')
            pass

def push(websocket_obj,message_obj):
    """!
    A non-busy forever loop pushes events to client.
    @param websocket_obj:  websocket object
    @param message_obj:  message object
    @return: void
    """
    while True:
        result = websocket_obj.recv()
        ## If result is not a ACK signal, in YAMCS case ACK for events looks like `[1,4,x]`
        if result.find('[1,4,')!=-1 :
            #result = tk.preProcess(result)


            message_obj.reply_channel.send({'text': result})
            message_obj.reply_channel.send({'text': result})
            message_obj.reply_channel.send({'text': result})
            tk.log('Event', 'BOUND', 'INFO')
            print message_obj.reply_channel.__dict__
            print result
        ## avoids busy-while-loop
        time.sleep(0.01)





def vid_connect( message):
    """!
    Accepts request and establishes a connection with client.
    @param message: connection request from client, this message will connection headers.
    @return: void
    """
    message.reply_channel.send({'accept': True})


def vid_disconnect( message):
    """!
    Accepts disconnection message and disconnects with client.
    @param message: disconnection request from client, this message will disconnection headers.
    @return: void
    """
    message.reply_channel.send({'close': True})


def getVideo( message):
    """!
    Invokes a continuous looping function which will push video images to client.
    @param message: invoke message from client.
    @return: void
    """
    name = message.content['text']
    VideoThroughUDP(message)


def VideoThroughUDP(msg_obj):
    """!
    Binds with UDP port and forwards image data as and when received from pyliner/yamcs.
    @param msg_obj: ivoke message passed as parameter in `getVideo' function.
    @return: void
    """
    ## UDP
    video_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    video_socket.bind(('', video_port))
    video_frame_counter= 0
    
    while True:
        ## buffer size is 65527 bytes
        data, addr = video_socket.recvfrom(65527)
        b64_img = base64.b64encode(data)
        video_frame_counter = video_frame_counter + 1
        msg_obj.reply_channel.send({'text': b64_img})
        #yield b64_img

        ## avoids busy-while-loop
        time.sleep(0.01)



'''
adsb_proc = {}

def adsb_connect(message):
    Feedback = json.dumps("ENDOK")
    message.reply_channel.send({'accept': True, 'text': Feedback})
    tk.log('ADSB', 'Connected.', 'INFO')

def adsb_disconnect(medssage):
    Feedback = json.dumps("ENDOK")
    message.reply_channel.send({'close': True, 'text': Feedback})
    tk.log('Instance', '(Dis)connected.', 'INFO')

def getAdsb(message):
    global adsb_proc,c
    client_id = message.content['reply_channel']
    message_text = tk.byteify(message.content['text'])
    if  message_text.find('initialize')!=-1:
        process = Process(target=push_adsb,args=(message,))
        process.start()
        adsb_proc[client_id]=process.pid
    elif  message_text.find('disolve')!=-1:
        for e in adsb_proc.keys():
            to_kill = psutil.Process(adsb_proc[e])
            to_kill.kill()
            del adsb_proc[e]
        print 'end'


def push_adsb(msg_obj):
    while True:
        response = urllib.urlopen('http://' + str(address) + ':8080/dump1090/data.json')
        d = json.loads(json.dumps(response.read()))
        msg_obj.reply_channel.send({'text':d})
        print d
        time.sleep(0.01)

'''
class MyCache:
    """!
   Loads launch variable to cache
    """
    def __init__(self):
        """!
        Initializes globally required variables from redis cache and other data structures that are helpful in tracking
        messages when the instance of this class is called in a multiprocess setting (or with multiple workers).
        """
        ## Initialize redis caching database
        self.redis_cache = redis.StrictRedis(host='localhost', port=6379, db=0)

    def initialize(self):
        """!
        Initializes redis cache with lauch variables which will persist through out the application.
        And performs certain housekeeping tasks.
        @return: void
        """
        try:
            with open(os.path.dirname(os.path.realpath(os.path.dirname(__file__))) + '/scripts/launch_config.json') as file:
                config = json.load(file)
                self.redis_cache.set ('instance',None)
                self.redis_cache.set('default_instance', config['pyliner']['default_instance'])
                self.redis_cache.set('address', config['pyliner']['address'])
                self.redis_cache.set('port', config['pyliner']['port'])
                self.redis_cache.set('video_port', config['pyliner']['video_port'])
                self.redis_cache.set('adsb_port', config['pyliner']['adsb_port'])
                self.redis_cache.set('number_of_workers', config['number_of_workers'])
                self.redis_cache.set('mode', config['mode'])
                self.redis_cache.set('app_path', config['app_path'])
                self.redis_cache.set('t_btn_cnt',0)

                ## clean test database, table
                if int(self.redis_cache.get('mode')) == 0:
                    conn = sqlite3.connect(self.redis_cache.get('app_path') + '/test_database', timeout=5)
                    c = conn.cursor()
                    ex = 'delete from TESTCASES'
                    c.execute(ex)
                    conn.commit()
                    conn.close()
            tk.log('Preconfiguration', 'Successful', 'INFO')
        except Exception as e:
            ## TODO: safely log error, unit test required
            tk.log('Preconfiguration', 'Faliure - '+str(e), 'ERROR')
            #tk.log('Preconfiguration', 'Faliure - '+str(e), 'ERROR')
            pass

