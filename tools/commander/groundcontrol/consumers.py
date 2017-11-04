import toolkit as tk
import urllib,json
from websocket import create_connection
from threading import Thread
from multiprocessing import Process
import psutil
import requests
from pprint import pprint
class IO:

    def __init__(self,instance,socket_name,address,port):
        self.socket_name = socket_name
        self.instance = instance
        self.address = address
        self.port = port
        self.isConnActive = True
        self.counter = 0


    def connect(self,message):
        self.isConnActive = True
        message.reply_channel.send({'accept': True})
        tk.log(self.socket_name,'CONNETED TO IO','INFO')



    def disconnect(self,message):
        self.isConnActive = False
        message.reply_channel.send({'close': True})
        tk.log(self.socket_name, 'DISCONNECTED FROM IO', 'INFO')

    def get(self):
        pass
    def post(self):
        pass


    def subscribe(self,message):

        message_text = message.content['text']


        if message_text == 'START_COMM_HS':
            tk.log(self.socket_name, 'GOT HS SIGNAL FROM CLIENT', 'INFO')
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif message_text == 'CLOSE_COMM_NOFBCK':
            tk.log(self.socket_name, 'GOT CLOSE SIGNAL FROM CLIENT', 'INFO')
            self.unsubscribe()
        else:
            received = ''
            to_send = ''

            if self.socket_name == 'PARAMETER':
                temp = tk.byteify(message_text)
                temp = json.loads(temp)
                temp = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(temp['tlm'])) + '}}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,' + str(self.counter) + ',' + str(temp) + ']'


            elif self.socket_name == 'EVENT':
                temp = '{"events": "subscribe"}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,' + str(self.counter) + ',' + str(temp) + ']'

            elif self.socket_name == 'EVENT':
                temp = '{"alarms": "subscribe"}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,' + str(self.counter) + ',' + str(temp) + ']'
            #while True:
            ws = create_connection('ws://' + self.address + ':' + self.port + '/' + self.instance + '/_websocket')
            ws.send(to_send)
            ## LAUNCING THREADS
            t = Thread(target=self.special_looping_over, args=[ws, message,self.counter])
            t.start()
            #while True:#self.isConnActive:
            #    result = ws.recv()
            #    print result
            #    if result != '[1,2,'+str(self.counter)+']':
            #        result = tk.preProcess(result)
            #        message.reply_channel.send({'text': result})
            #        tk.log(self.socket_name, 'BOUND', 'INFO')




    def unsubscribe(self):
        self.disconnect()

    def sokcetPost(self):
        pass

    def directoryListing(self,message):
        name = message.content['text']
        print '[' + tk.getDate() + ']' + name
        if name == 'START_COMM_HS':
            # Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif name == 'CLOSE_COMM_NOFBCK':
            print '[' + tk.getDate() + ']' + ' Server disconnecting...'
        else:
            response = tk.get_directory(name)
            data = json.dumps(response)
            # Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': data})
            print '[' + tk.getDate() + ']' + ' Packet ' + name + ' sent.'

    def special_looping_over(self,websocket_obj,message_obj,counter):
        while self.isConnActive:
            result = websocket_obj.recv()
            print result
            if result != '[1,2,' + str(counter) + ']':
                result = tk.preProcess(result)
                message_obj.reply_channel.send({'text': result})
                tk.log(self.socket_name, 'BOUND', 'INFO')




defaultInstance =None



class UnsubscribeTlmCommand:

    def __init__(self):
        self.defaultInstance= None
        self.port = 8090
        self.address = '127.0.0.1'
        self.tlmSeqNum = 0



    def connect(self,message):
        self.housekeeping()
        message.reply_channel.send({'accept': True})
        tk.log('','CONNETED TO IO','INFO')

    def disconnect(self,message):
        message.reply_channel.send({'close': True})
        tk.log('', 'DISCONNECTED FROM IO', 'INFO')


    def looseTlmCommand(self,message):
        message_text = message.content['text']
        if message_text == 'START_COMM_HS':
            tk.log('LOSTCOMM_HS', 'GOT HS SIGNAL FROM CLIENT', 'INFO')
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif message_text == 'CLOSE_COMM_NOFBCK':
            tk.log('LOSTCOMM_ACK', 'GOT CLOSE SIGNAL FROM CLIENT', 'INFO')
        else:
            tk.log('LOSTCOMM_MSG', 'GOT CLOSE SIGNAL FROM CLIENT', 'INFO')
            temp = tk.byteify(message_text)
            temp = json.loads(temp)
            temp = ' {"parameter":"unsubscribe", "data":{"list":' + str(tk.byteify(temp['tlm'])) + '}}'
            temp = temp.replace("\'", "\"")
            to_send = '[1,1,' + str(self.tlmSeqNum) + ',' + str(temp) + ']'
            ws = create_connection('ws://' + self.address + ':' + str(self.port) + '/'+self.defaultInstance+'/_websocket')
            ws.send(to_send)
            print '*******DISCON',to_send
            result = ws.recv()
            message.reply_channel.send({'text': result})
            tk.log('', 'BOUND', 'INFO')

            #ws.send(to_send)
            #t = Thread(target=self.special_looping_over, args=[ws, message, self.tlmSeqNum])
            #t.start()

    def housekeeping(self):
        json = tk.readSESSION()
        self.defaultInstance = json["InstanceName"]

    def special_looping_over(self,websocket_obj,message_obj,counter):
        while True:
            result = websocket_obj.recv()

            if result != '[1,2,' + str(counter) + ']':
                result = tk.preProcess(result)

# COMPLETE
class Telemetry:

    """
    All telemetry requests from the client side are channeled through an instance of Telemetry class.
    These requests are forwarded to pyliner or YAMCS through web sockets. A system process is created to listen to data on these sockets.
    All the information required to track each subscription is stored in a data structure called 'subscribers' which will be used later to
    properly unsubscribe to data and kill process generated.
    """

    def __init__(self):
        """
        Initializes data structures and assigned default values to constants.
        """
        self.subscribers = {}
        self.defaultInstance= None
        self.port = 8090
        self.address = '127.0.0.1'
        #self.tlmSeqNum = 0
        self.specialSeqNumber =0
        self.killed = 0


    def connect(self, message):
        """
        Sets default instance and accepts connection from client.
        :param message: message object
        :return: void
        """
        self.housekeeping()
        message.reply_channel.send({'accept': True})
        tk.log(self.defaultInstance,'Got Telemetry connection request from client','INFO')

    def disconnect(self, message):
        """
        Sends disconnect signal to client.
        :param message: message object
        :return: void
        """
        message.reply_channel.send({'close': True})
        tk.log('self.defaultInstance', 'Got Telemetry (dis)connection request from client', 'INFO')

    def looseTelemetry(self, message):
        """
        Process unsubscribe requests for telemetry and kills all processes related to a particular telemetry.
        :param message:message object
        :return: void
        """
        message_text = message.content['text']

        if message_text == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif message_text == 'CLOSE_COMM_NOFBCK':
            self.disconnect(message)

        elif message_text.find('tlm')!=-1:

        # Converting message text to hashable key.
            prepare1 = json.loads(tk.byteify(message_text))
            prepare1['tlm'][0].pop('format', None)
            prepare2 = json.dumps(prepare1)
            myUnit = self.subscribers[prepare2]

        # Converting message text to a format understood by pyliner or YAMCS.
            temp = tk.byteify(message_text)
            temp = json.loads(temp)
            temp = ' {"parameter":"unsubscribe", "data":{"list":' + str(tk.byteify(temp['tlm'])) + '}}'
            temp = temp.replace("\'", "\"")
            to_send = '[1,1,0,' + str(temp) + ']'

        # Get websocket object and process ID, kill process and send unsubscribe signal to pyliner or YAMCS
            ws = myUnit['ws']
            pid = myUnit['pid']
            process = myUnit['process']
            if process.is_alive():
                to_kill = psutil.Process(pid)
                to_kill.kill()
                self.killed=self.killed+1
            ws.send(to_send)
            self.subscribers.pop(prepare2,None)
            tk.log(message.content['text'], 'Telemetry push process is now killed.', 'INFO')

    def getTelemetry(self, message):
        """
        Process subscribe requests for telemetry and creates system processes which pushes data to client.
        :param message: message object
        :return: void
        """
        message_text = message.content['text']
        unit = {}

        if message_text == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif message_text == 'CLOSE_COMM_NOFBCK':
            self.disconnect(message)

        elif message_text.find('tlm')!=-1:

        # Converting message text to hashable key.
            prepare1 =json.loads(tk.byteify(message_text))
            prepare1['tlm'][0].pop('format',None)
            prepare2 = json.dumps(prepare1)

            key = prepare2
            process = None
            myID = self.specialSeqNumber

        # Converting message text to a format understood by pyliner or YAMCS.
            temp = tk.byteify(message_text)
            temp = json.loads(temp)
            temp = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(temp['tlm'])) + '}}'
            temp = temp.replace("\'", "\"")
            to_send = '[1,1,0,' + str(temp) + ']'

        # Connecting to pyliner or YAMCS via web sockets.
            if self.defaultInstance!=None:
                ws = create_connection('ws://' + str(self.address) + ':' + str(self.port) + '/'+str(self.defaultInstance)+'/_websocket')
            else:
                ws = create_connection('ws://' + str(self.address) + ':' + str(self.port) + '/'+str(self.getInstanceName())+'/_websocket')

        # Send message, start a system process, store current data in a local dict.
            ws.send(to_send)
            process = Process(target=self.push, args=(ws,message))
            process.start()
            pid = process.pid
            self.specialSeqNumber = self.specialSeqNumber + 1
            unit['myID'] = myID
            unit['message'] = message
            unit['process'] = process
            unit['pid'] = pid
            unit['ws'] = ws
            self.subscribers[key]=unit

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

    def push(self, websocket_obj, message_obj):
        """
        A forever loop to receive and push telemetry to client.
        :param websocket_obj:  websocket object
        :param message_obj: message object
        :return: void
        """
        while True:
            result = websocket_obj.recv()
            if result != '[1,2,0]':
                result = tk.preProcess(result)
                message_obj.reply_channel.send({'text': result})
                tk.log(message_obj.content['text'], 'Telemetry packet sent to client', 'INFO')

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
        self.housekeeping()
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

    def getCommandInfo(self, message):
        message_text = message.content['text']


        if message_text == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif message_text == 'CLOSE_COMM_NOFBCK':
            self.disconnect(message)

        else:
            print '**************************'
            print message_text
            print '**************************'
            if self.defaultInstance!=None:
                response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/mdb/'+ str(self.defaultInstance)+'/commands'+message_text)
            else:
                response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/mdb/'+ self.getInstanceName()+'/commands'+message_text)
            data = json.loads(json.dumps(response.read()))
            data = data.replace("\"", "\'")
            message.reply_channel.send({'text':data})


    def postCommand(self, message):
        message_text = message.content['text']


        if message_text == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif message_text == 'CLOSE_COMM_NOFBCK':
            self.disconnect(message)

        else:
            print '**************************'
            print message_text
            to_post = json.loads(message_text)
            print '**************************'
            url=''
            if self.defaultInstance!=None:
                url = 'http://' + str(self.address) + ':' + str(self.port) +'/ api / processors / ' + str(self.defaultInstance) + ' / realtime / commands / ' + to_post['name'] + '?nolink'
            else:
                url = 'http://' + str(self.address) + ':' + str(self.port) +'/ api / processors / ' + self.getInstanceName() + ' / realtime / commands / ' + to_post['name'] + '?nolink'

            msg = {
                'assignment': to_post['args'],
                'origin': 'user@host',
                'sequenceNumber': 0,
                'dryRun': False
            }
            requests.post(url=url, data=msg)




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
        tk.log('INSTANCE', 'CONNETED TO SOCKET', 'INFO')

    def disconnect(self, message):
        message.reply_channel.send({'close': True})
        tk.log('INSTANCE', 'DISCONNECTED FROM SOCKET', 'INFO')

    def getInstanceList(self, message):
        name = message.content['text']

        if name == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif name == 'CLOSE_COMM_NOFBCK':
            tk.log('GET INSTANCE LIST', 'DISCONNECTING FROM SOCKET', 'INFO')
        else:
            response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) + '/api/instances')
            data = json.loads(json.dumps(response.read()))
            message.reply_channel.send({'text': data})
            tk.log(name, 'PACKET SENT', 'INFO')

    def setDefaultInstance(self,message):
        name = message.content['text']
        if name == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        else:
            json = tk.readSESSION()
            json["InstanceName"]=name
            tk.writeSESSION(json)

class Directory:
    def connect(self,message):
        message.reply_channel.send({'accept': True})
        tk.log('','CONNETED TO IO','INFO')

    def disconnect(self,message):
        message.reply_channel.send({'close': True})
        tk.log('', 'DISCONNECTED FROM IO', 'INFO')


    def directoryListing(self,message):
        name = message.content['text']

        if name == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif name == 'CLOSE_COMM_NOFBCK':
            print '[' + tk.getDate() + ']' + ' Server disconnecting...'
        else:
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
        tk.log('','CONNETED TO IO','INFO')

    def disconnect(self,message):
        message.reply_channel.send({'close': True})
        tk.log('', 'DISCONNECTED FROM IO', 'INFO')


    def getEvents(self,message):
        message_text = message.content['text']
        if message_text == 'START_COMM_HS':
            tk.log('', 'GOT HS SIGNAL FROM CLIENT', 'INFO')
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif message_text == 'CLOSE_COMM_NOFBCK':
            tk.log('', 'GOT CLOSE SIGNAL FROM CLIENT', 'INFO')
        else:
            data = '[1, 1, 1, {"events": "subscribe"}]'
            ws = create_connection('ws://' + self.address + ':' + str(self.port) + '/'+self.getDefaultInstance()+'/_websocket')
            ws.send(data)
            t = Thread(target=self.special_looping_over, args=[ws, message, self.tlmSeqNum])
            t.start()

    def getDefaultInstance(self):
        json = tk.readSESSION()
        return json["InstanceName"]

    def housekeeping(self):
        json = tk.readSESSION()
        self.defaultInstance = json["InstanceName"]



    def special_looping_over(self,websocket_obj,message_obj,counter):
        while True:
            result = websocket_obj.recv()

            if result.find('[1,2,')==-1 :
                #result = tk.preProcess(result)
                message_obj.reply_channel.send({'text': result})
                print result
                tk.log('', 'BOUND', 'INFO')