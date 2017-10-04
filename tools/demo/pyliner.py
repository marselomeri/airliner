#!/usr/bin/python

from arte_ccsds import *
import pyliner_msgs

from pymitter import EventEmitter
from collections import namedtuple
import urllib2
import websocket
import thread
import time
from websocket import create_connection
import json
from os.path import exists,join
import time
import datetime
import message_pb2
import requests
import logging

DEFAULT_CI_PORT = 5009
DEFAULT_TO_PORT = 5012

class Pyliner(object):

    def __init__(self, **kwargs):
        self.address = kwargs.get("address", "localhost")
        self.ci_port = kwargs.get("ci_port", DEFAULT_CI_PORT)
        self.to_port = kwargs.get("to_port", DEFAULT_TO_PORT)
        self.airliner_data = self.__read_json(kwargs.get("airliner_map", None))
        self.subscribed_tlm = []

    def __read_json(self, file_path):
        """ Parses the required JSON input file containing Airliner mappings """
        if exists(file_path):
            with open(file_path, 'r') as airliner_map:
                return json.load(airliner_map)
        else:
            raise IOError #TODO
            
    def __get_airliner_op(self, op_path):
        """ Receive a ops name and returns a dict to that op """
        ret_op = None
        ops_names = op_path.split('/')
        print ops_names
        
        for fsw in self.airliner_data:
            if fsw == ops_names[0]:
                for app, app_data in fsw["apps"].iteritems():
                    if app_data["app_ops_name"] == ops_names[1]:
                        op = app["operations"][ops_names[2]]
                        ret_op = op if op else None

        return ret_op

    def __get_ccsds_msg(self, op_path):
        """ Receive a ops name and returns a ccsds msg """
        ret_msg = None
        op = self.__get_airliner_op(op_path)
        if not op:
            return ret_msg
            
        if op["airliner_cc"] == "-1": # TODO Check if int
            # Telemetry
            ret_msg = CCSDS_TlmPkt_t()
            ret_msg.init_packet()
            ret_msg.PriHdr.StreamId.bits.app_id = op["airliner_msg"] #TODO
        else:
            # Command
            ret_msg = CCSDS_CmdPkt_t()
            ret_msg.init_packet()
            ret_msg.PriHdr.StreamId.bits.app_id = op["airliner_msg"] #TODO
            ret_msg.SecHdr.Command.bits.code = op["airliner_cc"]
            ret_msg.set_checksum(0) #TODO

        return ret_msg

    def serialize(self, msg, payload):
        """ Receive a CCSDS message and payload then returns the serialized concatenation of them """
        return str(msg.get_encoded()) + payload.SerializeToString()

    def deserialize(self, msg, msg_id):
        """ Receive the payload of a message and deserializes it"""
        tlm_packet = CCSDS_TlmPkt_t()
        tlm_packet.set_decoded(msg[:12]) #TODO
        

    def create_pb_obj(self, script_cmd):
        """ Receives a cmd from the user script and initializes a pb obj of that type """
        op = self.__get_airliner_op(script_cmd["name"])
        if not op:
            return None
            
        pb_obj = proto_msg_map[op["airliner_msg"]]()
        assign = ""
        for arg in script_cmd["args"]:
            assign.append("pb_obj." + arg["name"] + " = " + arg["value"]

    def send_command(self, args):
        """ 
        """
        pass

    def recv_telemetry(self, args):
        """ 
        """
        pass
        
    def step_frame(self, steps = 1):
        """ Step passed number of frames """
        pass
        
    def recv_telemetry(self, args):
        """ 
        """
        pass

    def setDefaultInstance(self, name):
        err, self.defaultInstance = self.bindToInstance(name)
        self.emit("connect", self.defaultInstance['name'])

    def getCommandInfo(self, cmd, cb):
        apiUrl = 'http://' + self.address + ':' + `self.port` + '/api';
        url = apiUrl + '/mdb/' + self.defaultInstance['name'] + '/commands' + cmd.get('name')
        cmdInfo = urllib2.urlopen(url).read()
        cb(cmdInfo)

    def getActiveInstanceByName(self, name):
        for instance in self.activeInstances:
            if instance['name'] == name:
                return instance
        return None

    def bindToInstance(self, name):
        def runListener(*args):
                instance['client'].run_forever()
        instance = self.getActiveInstanceByName(name);
        if instance != None:
            # Instance is already bound.  Call the callback with the already bound
            # instance object.
            return None, instance
        else:
            # Instance is not bound.  Open a websocket to the server.
            url = 'ws://' + self.address + ':' + `self.port` + '/' + name + '/_websocket'
            instance = {'tlmSeqNum': 0, 'name': name, 'client':websocket.WebSocketApp(url,
                                                   on_message = self.onWsMessage,
                                                   on_error = self.onWsError,
                                                   on_close = self.onWsClose)}
            instance['client'].on_open = self.onWsOpen
            self.activeInstances.append(instance)
            thread.start_new_thread(runListener, ())
            return None, instance

    def onWsMessage(self, ws, message):
        obj = json.loads(message)
        #if obj[1] == 1:
        #    # Request
        #    print "Request"
        if obj[1] == 2:
            # Reply
            print "Reply"
        elif obj[1] == 3:
            # Exception
            print "Exception"
        elif obj[1] == 4:
            # Data
            for param in obj[3]['data']['parameter']:
                for subscriber in self.subscribers:
                    for tlmItem in subscriber['params']['tlm']:
                        if tlmItem['name'] == param['id']['name']:
                            if 'homogeneity' in subscriber['params']:
                                ## First store the parameter so we can compare homogeneity. */
                                tlmItem['sample'] = param;

                                # Get the optional parameters.
                                homogenousBy = 'acquisitionTime';
                                tolerance = 0;
                                if 'by' in subscriber['params']['homogeneity']:
                                    homogenousBy = subscriber['params']['homogeneity']['by']
                                if 'tolerance' in subscriber['params']['homogeneity']:
                                    tolerance = subscriber['params']['homogeneity']['tolerance']

                                # Now determine if the samples are homogenous.  First,
                                # Get the timestamp of the current sample.
                                timeStamp = datetime.datetime.fromtimestamp(param[homogenousBy] / 1000.0)

                                # Now iterate through the remaining samples.  If any
                                # of them fall outside the defined tolerance, flag
                                # this not homogenous.
                                isHomogenous = True
                                for tlmInner in subscriber['params']['tlm']:
                                    if 'sample' in tlmInner:
                                        sample = tlmInner['sample']
                                        sampleTimeStamp = datetime.datetime.fromtimestamp(sample[homogenousBy]/1000.0)
                                        diff = timeStamp - sampleTimeStamp
                                        if diff > datetime.timedelta(milliseconds=float(tolerance)):
                                            isHomogenous = False
                                            break
                                    else:
                                        isHomogenous = False
                                        break
                                if isHomogenous:
                                    # The sample group is homogenous.  Send the subscriber
                                    # an array containing the entire group.
                                    params = []
                                    for tlmInner in subscriber['params']['tlm']:
                                        params.append(tlmInner['sample'])
                                    subscriber['updateFunc'](params)
                            else:
                                # Homogeneity is not defined.  Just give it to the subscriber
                                # as its received.
                                subscriber['updateFunc'](param);

    def onWsError(self, ws, error):
        print error

    def onWsClose(self, ws):
        print "### closed ###"

    def onWsOpen(self, ws):
        print "on_open"

    def subscribeAfterBind(self, args, updateFunc, err, newInstance):
        print "bindComplete"
        #print newInstance
        #self.tlmSeqNum = self.tlmSeqNum + 1;
        # var msgOut = '[1,1,' + self.tlmSeqNum + ',' + JSON.stringify(msg) + ']';

    def subscribe(self, args, updateFunc):
        self.subscribers.append({'tlmSeqNum': 0, 'params':args, 'updateFunc':updateFunc});
        if 'instance' in args:
            # The caller specified an instance.  Get the specific instance.
            instance = self.getActiveInstanceByName(args['instance']);
            if instance == None:
                # We haven't bound this instance yet.  Bind it and defer the
                # subscription to after the bind is complete.
                err, newInstance = self.bindToInstance(args['instance'])
                newInstance['tlmSeqNum'] += 1
                msgOut = '[1,1,' + `newInstance['tlmSeqNum']` + ',{"parameter":"subscribe","data":{"list":' + json.dumps(args['tlm']) + '}}]'
                time.sleep(1)
                newInstance['client'].send(msgOut)
            else:
                # We have already bound this instance.  Just go ahead and subscribe.
                instance['tlmSeqNum'] += 1
                msgOut = '[1,1,' + `instance['tlmSeqNum']` + ',{"parameter":"subscribe","data":{"list":' + json.dumps(args['tlm']) + '}}]'
                instance['client'].send(msgOut)
        else:
            # The caller did not specify an instance.  Go ahead and just use the
            # default instance, if defined.
            self.defaultInstance['tlmSeqNum'] += 1
            msgOut = '[1,1,' + `self.defaultInstance['tlmSeqNum']` + ',{"parameter":"subscribe","data":{"list":' + json.dumps(args['tlm']) + '}}]'
            self.defaultInstance['client'].send(msgOut)

    def sendCommand(self, args):
        cmdMsg = message_pb2.IssueCommandRequest()
        cmdMsg.origin = "user@host"
        cmdMsg.sequenceNumber = self.cmdSeqNum
        cmdMsg.dryRun = False

        assignments = []

        if 'args' in args:
            for arg in args['args']:
                assignment = message_pb2.IssueCommandRequest.Assignment()
                assignment.name = arg['name']
                assignment.value = arg['value']
                assignments.append(assignment)

        cmdMsg.assignment.extend(assignments)
        path = 'http://' + self.address + ':' + `self.port` + '/api/processors/' + self.defaultInstance['name'] + '/realtime/commands/' + args['name'] + '?nolink';
        req = urllib2.Request(path, cmdMsg.SerializeToString(), {'Content-Type': 'application/protobuf', 'Accept': 'application/protobuf'})

        res = urllib2.urlopen(req)
        
        
            def __init__(self, address='localhost', ci_port=DEFAULT_CI_PORT, to_port=DEFAULT_TO_PORT):
        self.address = address
        self.ci_port = ci_port
        self.to_port = to_port
        self.subscribed_tlm = []
        self.airliner_data = self.__read_airliner_input()
