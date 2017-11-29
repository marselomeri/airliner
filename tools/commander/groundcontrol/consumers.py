import toolkit as tk
import urllib,json
from websocket import create_connection
from threading import Thread
from multiprocessing import Process,Lock,Value
from channels.sessions import channel_session
import psutil
import requests
import time
import socket
import base64
from channels import Group

import redis


class Telemetry:

    def __init__(self):
        """
        Initializes data structures and assigned default values to constants.
        """
        self.r = redis.StrictRedis(host='localhost', port=6379, db=0)
        self.defaultInstance= tk.getStuffFromSession('ins_name')
        self.port = tk.getStuffFromSession('port')
        self.address = tk.getStuffFromSession('address')
        self.yamcs_ws = create_connection('ws://' + str(self.address) + ':' + str(self.port) + '/'+str(self.defaultInstance)+'/_websocket')


        self.sock_map = {}
        self.proc_map = {}
        self.subscribers = []
        #self.tlmSeqNum = 0
        self.process = []
        self.tracker =0


    def connect(self, message):
        """
        Sets default instance and accepts connection from client.
        :param message: message object
        :return: void
        """
        self.housekeeping()

        #message.reply_channel.send({'close': True})
        Group('tlm_bc').add(message.reply_channel)
        message.reply_channel.send({'accept': True})
        #print self.sock_map


    def disconnect(self, message):
        """
        Sends disconnect signal to client.
        :param message: message object
        :return: void
        """

        message.reply_channel.send({'close': True})
        Group('tlm_bc').discard(message.reply_channel)
        tk.log('Instance', '(Dis)connected.', 'INFO')



    def looseTelemetry(self, message):
        """
        Process unsubscribe requests for telemetry and kills all processes related to a particular telemetry.
        :param message:message object
        :return: void
        """
        message_text = message.content['text']
        if message_text.find('tlm')!=-1:
            """
            msg_text_obj = json.loads(message_text)
            tlm_name = msg_text_obj['tlm'][0]['name']
            message_client_id = message.content['reply_channel']
            cl_obj = json.loads(self.r.get('clients'))

            validation_counter = 0

            for each_key in cl_obj:
                if each_key == message_client_id:
                    print 'skip'
                else:
                    if tlm_name in cl_obj[each_key]['subscribers']:
                        validation_counter +=1

            if validation_counter == 0:
                try:
                    # Converting message text to a format understood by pyliner or YAMCS.
                    temp = tk.byteify(message_text)
                    temp = json.loads(temp)
                    temp = ' {"parameter":"unsubscribe", "data":{"list":' + str(tk.byteify(temp['tlm'])) + '}}'
                    temp = temp.replace("\'", "\"")
                    to_send = '[1,1,0,' + str(temp) + ']'
                    self.yamcs_ws.send(to_send)

                    for each_key in cl_obj:
                        try:
                            cl_obj[each_key]['subscribers'].remove(tlm_name)
                        except:
                            print 'pass'
                            pass

                    tk.log(message_text, 'Telemetry push process killed.', 'INFO')
                except:
                    tk.log(message_text, 'Telemetry push process ALREADY KILLED.', 'INFO')
            #this_obj = cl_obj[message_client_id]
        #subscribers = this_obj['subscribers']

        elif message_text == 'USALL' :
            #for p in self.process:
            self.yamcs_ws.send_close(500, 'hello')
            #ws.abort()
            #to_kill = psutil.Process(self.process[i].pid)
            #to_kill.kill()
            #time.sleep(1)
            #self.tracker = 0
            #self.process = []
        """




    def getTelemetry(self, message):
        """
        Process subscribe requests for telemetry and creates system processes which pushes data to client.
        :param message: message object
        :return: void
        """
        message_client_id = message.content['reply_channel']


        message_text = tk.byteify(message.content['text'])
        print message_client_id,message_text

        if message_text.find('kill_tlm') != -1:
            msg = message_text.replace('kill_tlm', '')
            msg_text_obj = json.loads(msg)
            temp = ' {"parameter":"unsubscribe", "data":{"list":' + str(tk.byteify(msg_text_obj['tlm'])) + '}}'
            temp = temp.replace("\'", "\"")
            to_send = '[1,1,0,' + str(temp) + ']'
            self.sock_map[message_client_id].send(to_send)
            print 'killed'

        elif message_text.find('usall')!=-1:
            try:
                to_kill_pid = self.proc_map[message_client_id]
                to_kill = psutil.Process(to_kill_pid)
                to_kill.kill()
                print 'killed processs'

            except:
                pass
        elif message_text.find('tlm')!=-1:

            msg_text_obj = json.loads(message_text)
            tlm_name = msg_text_obj['tlm'][0]['name']

            #if tlm_name not in self.subscribers:
            # Converting message text to a format understood by pyliner or YAMCS.

            #self.subscribers.append(tlm_name)
            temp = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(msg_text_obj['tlm'])) + '}}'
            temp = temp.replace("\'", "\"")
            to_send = '[1,1,0,' + str(temp) + ']'

        # Send message, start a system process, store current data in a local dict.

            # Qne time per application cycle.
            if message_client_id not in self.sock_map.keys():
                client_id = message.content['reply_channel']
                ws = create_connection('ws://' + str(self.address) + ':' + str(self.port) + '/' + str(self.defaultInstance) + '/_websocket')
                self.sock_map[client_id] = ws
                self.sock_map[message_client_id].send(to_send)
                process = Process(target=self.push,args=(self.sock_map[message_client_id],))
                process.start()
                self.proc_map[client_id] = process.pid
                self.tracker=self.tracker+1
                #print self.sock_map
            else:
                self.sock_map[message_client_id].send(to_send)






    def housekeeping(self):
        """
        Reads config file 'session.json' and sets default instance value.
        :return: void
        """
        json = tk.readSESSION()
        self.defaultInstance = json["InstanceName"]

    def getInstanceName(self):
        """
        Reads config file 'session.json' and returns default instance value.
        :return: string
        """
        json = tk.readSESSION()
        return json["InstanceName"]

    def push(self, websocket_obj):
        """
        A forever loop to receive and push telemetry to client.
        :param websocket_obj:  websocket object
        :param message_obj: message object
        :return: void
        """

        while True:
            try:

                result = websocket_obj.recv()

                if result != '[1,2,0]':
                    #print message_obj.content['reply_channel'], tk.introspectResult(result)
                    result2 = tk.preProcess(result)
                    try:
                        Group('tlm_bc').send({'text': result2})
                    except:
                        time.sleep(1)
                        Group('tlm_bc').send({'text': result2})
                time.sleep(0.01)
                #print message_obj.content['reply_channel'], tk.introspectResult(result)
            except:
                print 'EOWHILE'
                break
                #print '\n\n---batch---\n'


                #print '\n---eob---\n\n'


class Command:

    def __init__(self):
        """
        Initializes data structures and assigned default values to constants.
        """
        #self.subscribers = {}
        self.defaultInstance = None
        self.port = 8090
        self.address = '127.0.0.1'
        # self.tlmSeqNum = 0
        #self.specialSeqNumber = 0
        #self.killed = 0

    def connect(self, message):
        """
        Sets default instance and accepts connection from client.
        :param message: message object
        :return: void
        """
        message.reply_channel.send({'accept': True})
        self.housekeeping()
        tk.log(self.defaultInstance,'Got Commanding connection request from client','INFO')

    def disconnect(self, message):
        """
        Sends disconnect signal to client.
        :param message: message object
        :return: void
        """
        message.reply_channel.send({'close': True})
        tk.log('self.defaultInstance', 'Got Commanding (dis)connection request from client', 'INFO')

    def getCommandInfo(self, message):

        message_text = message.content['text']
        #print '**************************'
        #print '==> ', message_text
        #print '**************************'
        if message_text == 'HS':
            message.reply_channel.send({'text': 'HSOK'})
        else:
            if self.defaultInstance!=None:
                response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/mdb/'+ str(self.defaultInstance)+'/commands'+message_text)
            else:
                response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/mdb/'+ self.getInstanceName()+'/commands'+message_text)

            data = json.loads(json.dumps(response.read()))
            data = data.replace("\"", "\'")


            message.reply_channel.send({'text':data})
            #time.sleep(5);
            #message.reply_channel.send({'text': 'HSOK'})


    def postCommand(self, message):
        message_text = message.content['text']

        #self.preProcessCommand(message_text)

        to_post = json.loads(message_text)
        print to_post
        print type(to_post)

        url=''
        if self.defaultInstance!=None:
            url = 'http://' + str(self.address) + ':' + str(self.port) +'/api/processors/' + str(self.defaultInstance) + '/realtime/commands' + to_post['name'] + '?nolink'
        else:
            url = 'http://' + str(self.address) + ':' + str(self.port) +'/api/processors/' + self.getInstanceName() + '/realtime/commands' + to_post['name'] + '?nolink'

        msg = '{"sequenceNumber": 0,"origin": "user@my-machine","assignment":'+ str(json.dumps(to_post['args']))+',"dryRun": false}'
        headers = {
            'Content-Type': 'application/json',
            'Accept': 'application/json'
        }
        #msg = json.dumps(msg)
        r = requests.post(url=url, data=msg, headers = headers)
        got = r.text
        message.reply_channel.send({'text': got})
        #print '**************************'
        #print msg
        #print got
        #to_post = json.loads(message_text)
        #print '**************************'

    def preProcessCommand(self,message_text):

        tk.log(type(message_text),'','')
        cmd_slug = json.loads(tk.byteify(message_text))
        tk.log(cmd_slug,'','')
        response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/mdb/' + self.getInstanceName() + '/commands' + cmd_slug['cmd']['name'])
        data = json.loads(json.dumps(response.read()))
        tk.log(data, '', '')

    def housekeeping(self):
        """
        Reads config file 'session.json' and sets default instance value.
        :return: void
        """
        json = tk.readSESSION()
        self.defaultInstance = json["InstanceName"]

    def getInstanceName(self):
        """
        Reads config file 'session.json' and returns default instance value.
        :return: string
        """
        json = tk.readSESSION()
        return json["InstanceName"]

class Instance:
    def __init__(self):
        self.port = 8090
        self.address = '127.0.0.1'

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
        json = tk.readSESSION()
        json["InstanceName"]=name
        tk.writeSESSION(json)


        #message.reply_channel.send({'close': True})

class Directory:
    def connect(self,message):
        message.reply_channel.send({'accept': True})

    def disconnect(self,message):
        message.reply_channel.send({'close': True})



    def directoryListing(self,message):
        name = message.content['text']
        print message
        response = tk.get_directory(name)
        data = json.dumps(response)
        message.reply_channel.send({'text': data})
        print '[' + tk.getDate() + ']' + ' Packet ' + name + ' sent.'

class Event:
    def __init__(self):

        self.port = 8090
        self.address = '127.0.0.1'
        self.tlmSeqNum = 0



    def connect(self,message):
        self.housekeeping()
        message.reply_channel.send({'accept': True})


    def disconnect(self,message):
        message.reply_channel.send({'close': True})



    def getEvents(self,message):
        message_text = message.content['text']
        data = '[1, 1, 1, {"events": "subscribe"}]'
        ws = create_connection('ws://' + self.address + ':' + str(self.port) + '/'+self.getDefaultInstance()+'/_websocket')
        ws.send(data)
        t = Thread(target=self.push, args=[ws, message])
        t.start()

    def getDefaultInstance(self):
        json = tk.readSESSION()
        return json["InstanceName"]

    def housekeeping(self):
        json = tk.readSESSION()
        self.defaultInstance = json["InstanceName"]



    def push(self,websocket_obj,message_obj):
        while True:
            result = websocket_obj.recv()

            if result.find('[1,4,')!=-1 :
                #result = tk.preProcess(result)
                message_obj.reply_channel.send({'text': result})
                print result
                tk.log('', 'BOUND', 'INFO')

class Misc:
    def __init__(self):

        self.mapping = {
            'ADSB':'http://127.0.0.1:9000/test'
        }
        self.port = 8090
        self.address = '127.0.0.1'

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

class Video:
    def __init__(self):
        self.address = '127.0.0.1'
        self.video_port = 3001
        self.video_frame_counter = 0
        self.video_socket = None

    def connect(self, message):
        print 'plug0'
        message.reply_channel.send({'accept': True})


    def disconnect(self, message):
        message.reply_channel.send({'close': True})


    def getVideo(self, message):
        print 'plug0.5'
        name = message.content['text']
        #buff = \
        self.VideoThroughUDP(message)
        #message.reply_channel.send({'text': buff})

    def VideoThroughUDP(self,msg_obj):
        UDP_IP = self.address
        UDP_PORT = self.video_port
        self.video_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)  # UDP
        self.video_socket.bind(("", UDP_PORT))
        print 'plug1'
        while True:
            print 'plug2'
            data, addr = self.video_socket.recvfrom(65527)  # buffer size is 1024 bytes
            b64_img = base64.b64encode(data)
            self.video_frame_counter = self.video_frame_counter + 1
            print 'Frame# : ['+str(self.video_frame_counter)+'] sent.'
            msg_obj.reply_channel.send({'text': b64_img})
            #yield b64_img

