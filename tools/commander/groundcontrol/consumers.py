import toolkit as tk
import urllib,json,os
from websocket import create_connection
from multiprocessing import Process
import psutil,requests,time,socket,base64
from channels import Group
import redis,sqlite3
from django import db


class Telemetry:

    def __init__(self):
        """
        Initializes data structures and assigned default values to constants.
        """
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)

        self.mode = int(self.r.get('mode'))
        self.db_path = self.r.get('app_path')
        self.number_of_workers = self.r.get('number_of_workers')
        self.defaultInstance= self.r.get('instance')
        self.port = self.r.get('port')
        self.address = self.r.get('address')

        self.sock_map = {}
        self.proc_map = {}
        self.subscribers = []
        self.process = []

        self.tracker =0
        self.test_flag = False
        self.test_sampling_frequency = (1.0/10)

    def connect(self, message):
        """
        Sets default instance and accepts connection from client.
        :param message: message object
        :return: void
        """

        Group('tlm_bc').add(message.reply_channel)
        message.reply_channel.send({'accept': True})
        tk.log('Instance', 'Connected.', 'INFO')

    def disconnect(self, message):
        """
        Sends disconnect signal to client.
        :param message: message object
        :return: void
        """
        message.reply_channel.send({'close': True})
        Group('tlm_bc').discard(message.reply_channel)
        tk.log('Instance', '(Dis)connected.', 'INFO')

    def test_db_wrapper(self,input,output,code,desc):
        if self.mode == 0:
            print 'TEST.....'
            conn = sqlite3.connect(self.db_path + '/test_database', timeout=5)
            tk.collectTestCases(conn, code, input, output, desc)
            conn.commit()
            conn.close()

    def getTelemetry(self, message):
        """
        Process subscribe requests for telemetry and creates system processes which pushes data to client.
        :param message: message object
        :return: void
        """
        message_client_id = message.content['reply_channel']
        message_text = tk.byteify(message.content['text'])
        #print  message_text


        if message_text.find('kill_tlm') != -1:

            try:

                msg = message_text.replace('kill_tlm', '')
                #print message_text
                #print json.loads(msg)

                #print type(msg)
                msg_text_obj = json.loads(msg)

                temp = ' {"parameter":"unsubscribe", "data":{"list":' + str(tk.byteify(msg_text_obj['tlm'])) + '}}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,0,' + str(temp) + ']'

                # TRAIN
                self.test_db_wrapper(message_text,'null','KILTLM','unsubscribe telemetry')

                self.sock_map[message_client_id].send(to_send)
                #print self.sock_map[message_client_id]
                tk.log('Instance', '[UNSUBSCRIBED] - '+message_client_id+' - '+msg, 'DEBUG')
            except:
                tk.log('Instance', '[ERR - UNSUBSCRIBED] - ' + message_client_id + ' - ' + message_text, 'ERROR')
                pass


        elif message_text.find('USALL')!=-1:
            try:
                print '..'
                to_kill_pid = self.proc_map[message_client_id]
                to_kill = psutil.Process(to_kill_pid)
                to_kill.kill()
                tk.log('Instance', '[KILLED] - ' + str(to_kill_pid), 'DEBUG')

            except:
                print '..'
                pass





        elif message_text.find('tlm')!=-1:

            msg_text_obj = json.loads(message_text)
            temp = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(msg_text_obj['tlm'])) + '}}'
            temp = temp.replace("\'", "\"")
            to_send = '[1,1,0,' + str(temp) + ']'

        # Send message, start a system process, store current data in a local dict.

            # TRAIN
            self.test_db_wrapper(message_text, 'null', 'SUBTLM', 'subscribe telemetry')

            # Qne time per application cycle.
            if message_client_id not in self.sock_map.keys():
                try:
                    client_id = message.content['reply_channel']
                    ws = create_connection('ws://' + str(self.address) + ':' + str(self.port) + '/' + self.r.get('instance') + '/_websocket')
                    self.sock_map[client_id] = ws
                    self.sock_map[message_client_id].send(to_send)
                    process = Process(target=self.push,args=(self.sock_map[message_client_id],))
                    process.start()
                    self.proc_map[client_id] = process.pid
                    self.tracker=self.tracker+1
                    tk.log('Instance', '[PROCESS] - ' + str(process.pid) , 'DEBUG')
                except:
                    tk.log('Instance', '[ERR - PROCESS] - ' + message_client_id + ' - ' + message_text, 'ERROR')
                    pass
            else:
                self.sock_map[message_client_id].send(to_send)
                tk.log('Instance', '[SUBSCRIBED] - ' + message_client_id + ' - ' + message_text, 'DEBUG')

    def push(self, websocket_obj):
        """
        A forever loop to receive and push telemetry to client.
        :param websocket_obj:  websocket object
        :param message_obj: message object
        :return: void
        """
        freq_count = 1
        while True:
            try:
                result = websocket_obj.recv()
                if result != '[1,2,0]':
                    result2 = tk.preProcess(result)

                    # TRAIN
                    if self.test_sampling_frequency*freq_count == 1 :
                        self.test_db_wrapper(result, result2, 'PREPROCTLM', 'preprocess telemetry before sending')
                        freq_count = 1
                    freq_count+=1

                    try:
                        Group('tlm_bc').send({'text': result2})
                        #print '@'
                    except:
                        time.sleep(1)
                        Group('tlm_bc').send({'text': result2})
                        #print '#',result2
            except:
                tk.log('Instance', 'Not able to push messages to client. Process killed.', 'ERROR')
                break
            time.sleep(0.01)# avoid busy loop

class Command:

    def __init__(self):
        """
        Initializes data structures and assigned default values to constants.
        """
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)

        self.mode = int(self.r.get('mode'))
        self.db_path = self.r.get('app_path')
        self.number_of_workers = self.r.get('number_of_workers')

        self.defaultInstance = self.r.get('instance')
        self.port = self.r.get('port')
        self.address = self.r.get('address')
        # self.tlmSeqNum = 0

    def connect(self, message):
        """
        Sets default instance and accepts connection from client.
        :param message: message object
        :return: void
        """
        message.reply_channel.send({'accept': True})
        tk.log(self.defaultInstance,'Got Commanding connection request from client','INFO')

    def disconnect(self, message):
        """
        Sends disconnect signal to client.
        :param message: message object
        :return: void
        """
        message.reply_channel.send({'close': True})
        tk.log('self.defaultInstance', 'Got Commanding (dis)connection request from client', 'INFO')

    def test_db_wrapper(self,input,output,code,desc):
        if self.mode == 0:
            print 'TEST.....'
            conn = sqlite3.connect(self.db_path + '/test_database', timeout=5)
            tk.collectTestCases(conn, code, input, output, desc)
            conn.commit()
            conn.close()

    def getCommandInfo(self, message):

        message_text = message.content['text']
        if message_text == 'HS':
            message.reply_channel.send({'text': 'HSOK'})
        else:
            if self.defaultInstance!='None':
                response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/mdb/'+ str(self.defaultInstance)+'/commands'+message_text)
            else:
                response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/mdb/'+ self.r.get('default_instance')+'/commands'+message_text)


            data = json.loads(json.dumps(response.read()))
            data = data.replace("\"", "\'")

            # TRAIN
            self.test_db_wrapper(message_text, data, 'CMDINFO', 'commanding information')

            message.reply_channel.send({'text':data})



    def postCommand(self, message):
        message_text = message.content['text']
        to_post = json.loads(message_text)
        url=''
        if self.defaultInstance!='None':
            url = 'http://' + str(self.address) + ':' + str(self.port) +'/api/processors/' + str(self.defaultInstance) + '/realtime/commands' + to_post['name'] + '?nolink'
        else:
            url = 'http://' + str(self.address) + ':' + str(self.port) +'/api/processors/' + self.r.get('default_instance') + '/realtime/commands' + to_post['name'] + '?nolink'

        msg = '{"sequenceNumber": 0,"origin": "user@my-machine","assignment":'+ str(json.dumps(to_post['args']))+',"dryRun": false}'
        headers = {
            'Content-Type': 'application/json',
            'Accept': 'application/json'
        }
        #print url
        #print msg
        #print headers
        r = requests.post(url=url, data=msg, headers = headers)

        # TRAIN
        self.test_db_wrapper(message_text, r.status_code, 'CMDPOST', 'sending commands')

        got = r.text
        print got
        self.r.set('t_btn_cnt',str((int(self.r.get('t_btn_cnt'))+1)))
        op = json.dumps({"cmd":got,"code":r.status_code})
        message.reply_channel.send({'text': op})

class Instance:
    def __init__(self):
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)
        self.defaultInstance = self.r.get('instance')
        self.port = self.r.get('port')
        self.address = self.r.get('address')


    def connect(self, message):
        message.reply_channel.send({'accept': True})


    def disconnect(self, message):
        message.reply_channel.send({'close': True})


    def getInstanceList(self, message):

        name = message.content['text']
        response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/instances')
        data = json.loads(json.dumps(response.read()))
        message.reply_channel.send({'text': data})


    def setDefaultInstance(self,message):
        name = message.content['text']
        self.defaultInstance = name
        self.r.set('instance',name)

class Directory:
    def __init__(self):
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)

        self.mode = int(self.r.get('mode'))
        self.db_path = self.r.get('app_path')

        self.number_of_workers = self.r.get('number_of_workers')

    def connect(self,message):
        message.reply_channel.send({'accept': True})

    def disconnect(self,message):
        message.reply_channel.send({'close': True})

    def test_db_wrapper(self,input,output,code,desc):
        if self.mode == 0:
            print 'TEST.....'
            conn = sqlite3.connect(self.db_path + '/test_database', timeout=5)
            tk.collectTestCases(conn, code, input, output, desc)
            conn.commit()
            conn.close()

    def directoryListing(self,message):
        name = message.content['text']
        response = tk.get_directory(name)
        data = json.dumps(response)

        # TRAIN
        self.test_db_wrapper(name, data,'DIR','obtain directory listing')

        message.reply_channel.send({'text': data})
        tk.log('Directory',' Packet ' + name + ' sent.','INFO')

class Event:#TODO
    def __init__(self):
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)


        self.defaultInstance = self.r.get('instance')
        self.port = self.r.get('port')
        self.address = self.r.get('address')

        self.proc_map = {}
        self.sock_map = {}
        self.tlmSeqNum = 0

    def connect(self,message):
        message.reply_channel.send({'accept': True})


    def disconnect(self,message):
        message.reply_channel.send({'close': True})



    def getEvents(self,message):
        message_text = message.content['text']
        client_id = message.content['reply_channel']
        if message_text == 'INVOKE':

            data = '[1, 1, 1, {"events": "subscribe"}]'
            ws = None
            if self.defaultInstance == 'None':
                ws = create_connection('ws://' + self.address + ':' + str(self.port) + '/'+self.r.get('default_instance')+'/_websocket')
            else:
                ws = create_connection('ws://' + self.address + ':' + str(self.port) + '/'+self.defaultInstance+'/_websocket')
            ws.send(data)
            print (data)
            t = Process(target=self.push, args=(ws, message))
            self.proc_map[client_id] = t.pid
            self.sock_map[client_id] = ws
            t.start()


        elif message_text =='KILLSWITCH':

            try:
                us_sock = self.sock_map[client_id]
                data = '[1, 1, 1, {"events": "unsubscribe"}]'
                us_sock.send(data)
                tk.log('Event', '[UNSIBSCRIBED] - ' + client_id+' events', 'DEBUG')
            except:
                tk.log('Event','Unable to unsubscribe.','ERROR')
                pass
            try:
                to_kill_pid = self.proc_map[client_id]
                to_kill = psutil.Process(to_kill_pid)
                to_kill.kill()
                tk.log('Event', '[KILLED] - ' + to_kill_pid, 'DEBUG')
            except:
                tk.log('Event', 'Unable to kill.', 'ERROR')
                pass





    def push(self,websocket_obj,message_obj):
        while True:
            result = websocket_obj.recv()
            print result
            if result.find('[1,4,')!=-1 :
                #result = tk.preProcess(result)
                print result
                message_obj.reply_channel.send({'text': result})
                print result
                tk.log('', 'BOUND', 'INFO')
            time.sleep(0.01)
#TODO
class Misc:
    def __init__(self):

        self.mapping = {
            'ADSB':'http://127.0.0.1:9000/test'
        }
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)
        self.defaultInstance = self.r.get('instance')
        self.port = self.r.get('port')
        self.address = self.r.get('address')

    def connect(self, message):
        message.reply_channel.send({'accept': True})


    def disconnect(self, message):
        message.reply_channel.send({'close': True})



    def getMisc(self, message):
        name = message.content['text']

        if name == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif name == 'CLOSE_COMM_NOFBCK':
            tk.log('GET INSTANCE LIST', 'DISCONNECTING FROM SOCKET', 'INFO')
        else:
            response = urllib.urlopen(self.mapping[name])
            data = json.loads(json.dumps(response.read()))
            message.reply_channel.send({'text': data})
            tk.log(name, 'PACKET SENT', 'INFO')
#TODO
class Video:
    def __init__(self):
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)
        self.defaultInstance = self.r.get('instance')
        self.video_port = self.r.get('video_port')
        self.address = self.r.get('address')
        self.video_frame_counter = 0
        self.video_socket = None

    def connect(self, message):
        message.reply_channel.send({'accept': True})


    def disconnect(self, message):
        message.reply_channel.send({'close': True})


    def getVideo(self, message):
        name = message.content['text']
        self.VideoThroughUDP(message)


    def VideoThroughUDP(self,msg_obj):
        UDP_IP = self.address
        UDP_PORT = self.video_port
        self.video_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)  # UDP
        self.video_socket.bind(("", UDP_PORT))
        while True:
            data, addr = self.video_socket.recvfrom(65527)  # buffer size is 1024 bytes
            b64_img = base64.b64encode(data)
            self.video_frame_counter = self.video_frame_counter + 1
            print 'Frame# : ['+str(self.video_frame_counter)+'] sent.'
            msg_obj.reply_channel.send({'text': b64_img})
            #yield b64_img

class MyCache:

    def __init__(self):
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)

    def initialize(self):
        with open(os.getcwd() + '/scripts/launch_config.json') as file:
            config = json.load(file)
            self.r.set ('instance',None)
            self.r.set('default_instance', config['pyliner']['default_instance'])
            self.r.set('address', config['pyliner']['address'])
            self.r.set('port', config['pyliner']['port'])
            self.r.set('video_port', config['pyliner']['video_port'])
            self.r.set('adsb_port', config['pyliner']['adsb_port'])
            self.r.set('number_of_workers', config['number_of_workers'])
            self.r.set('mode', config['mode'])
            self.r.set('app_path', config['app_path'])
            self.r.set('t_btn_cnt',0)

            #clean table
            if int(self.r.get('mode')) == 0:
                conn = sqlite3.connect(self.r.get('app_path') + '/test_database', timeout=5)
                c = conn.cursor()
                ex = 'delete from TESTCASES'
                c.execute(ex)
                conn.commit()
                conn.close()

