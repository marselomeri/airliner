#!/usr/bin/python

from arte_ccsds import *
from datetime import datetime, timedelta
import json
import logging
from os import mkdir
from os.path import exists,join
import python_pb.pyliner_msgs as pyliner_msgs
import socket
import SocketServer
import threading

DEFAULT_CI_PORT = 5009
DEFAULT_TO_PORT = 5012

# Custom exceptions
class InvalidCommand(Exception): pass

class Pyliner(object):

    def __init__(self, **kwargs):
        self.address = kwargs.get("address", "localhost")
        self.ci_port = kwargs.get("ci_port", DEFAULT_CI_PORT)
        self.to_port = kwargs.get("to_port", DEFAULT_TO_PORT)
        self.test_name = kwargs.get("test_name", "Unspecified")
        self.airliner_data = self.__read_json(kwargs.get("airliner_map", None))
        self.ci_socket = self.__init_socket()
        self.to_socket = self.__init_socket()
        self.subscribers = []
        self.tlm_listener = SocketServer.UDPServer((self.address, DEFAULT_TO_PORT), self.__server_factory(self.__on_recv_telemetry))
        self.listener_thread = threading.Thread(target=self.tlm_listener.serve_forever)
        self.passes = 0
        self.fails = 0
        self.start_time = datetime.now()
        self.log_dir = kwargs.get("log_dir", "./logs/")
        self.log_name = self.start_time.strftime("%Y-%m-%d_%I:%M:%S") + "_pyliner_" + self.test_name + ".log"
        self.all_telemetry = []
        self.__setup_log()
        self.ingest_active = True
        self.recv_telemetry()

    def __init_socket(self):
        """ Creates a UDP socket object and returns it """
        return socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
    def __server_factory(self, callback):
        """ Creates server object and sets the callback """
        def create_handler(*args, **kwargs):
            return ThreadedUDPRequestHandler(callback, *args, **kwargs)
        return create_handler

    def __read_json(self, file_path):
        """ Parses the required JSON input file containing Airliner mappings """
        try:
            with open(file_path, 'r') as airliner_map:
                return json.load(airliner_map)
        except IOError:
            print "Specified input file (%s) does not exist" % file_path
        except Exception as e:
            print e
    
    def __setup_log(self):
        """ Setup log for Pyliner """
        if not exists(self.log_dir):
            mkdir(self.log_dir)
            
        logging.basicConfig(format='%(asctime)s\t%(levelname)s: %(message)s', 
                            datefmt='%m/%d/%Y %I:%M:%S %p',
                            filename=join(self.log_dir, self.log_name),
                            level=logging.DEBUG)
            
    def __get_airliner_op(self, op_path):
        """ Receive a ops path and returns the dict for that op defined in the input file """
        ret_op = None
        ops_names = op_path.split('/')[1:]
        
        for fsw, fsw_data in self.airliner_data.iteritems():
            if fsw == ops_names[0]:
                for app, app_data in fsw_data["apps"].iteritems():
                    if app_data["app_ops_name"] == ops_names[1]:
                        op = app_data["operations"][ops_names[2]]
                        ret_op = op if op else None

        return ret_op

    def __get_ccsds_msg(self, op):
        """ Receive a ops dict and returns a ccsds msg """
        # If the command code is -1 this is telemetry
        if op["airliner_cc"] == "-1":
            ret_msg = CCSDS_TlmPkt_t()
            ret_msg.init_packet()
            ret_msg.PriHdr.StreamId.bits.app_id = int(op["airliner_mid"], 0)
        else:
            ret_msg = CCSDS_CmdPkt_t()
            ret_msg.clear_packet()
            ret_msg.init_packet()
            ret_msg.PriHdr.StreamId.bits.app_id = int(op["airliner_mid"], 0)
            ret_msg.SecHdr.Command.bits.code = int(op["airliner_cc"])
        
        return ret_msg

    def serialize(self, header, payload):
        """ Receive a CCSDS message and payload then returns the serialized concatenation of them """
        if not payload:
            return str(header.get_encoded())    
        else:
            return str(header.get_encoded()) + payload.SerializeToString()

    def _get_op_attr(self, op_path, op_attr):
        """ Gets the operation path from airliner data for a specified attribute 
        
        Args:
            op_path(str): Operation path as located in input file (E.g. "/Airliner/ES/Noop")
            op_attr(str): Operational name of message attribute (E.g. CmdCounter)
            
        Returns:
            True path to access this attribute in protobuf message (E.g. Payload.CmdCounter)
        """
        op = self.__get_airliner_op(op_path)
        ops_names = op_path.split('/')[1:]
        for fsw, fsw_data in self.airliner_data.iteritems():
            if fsw == ops_names[0]:
                for app, app_data in fsw_data["apps"].iteritems():
                    if app_data["app_ops_name"] == ops_names[1]:
                        for op_name, op_data in app_data["proto_msgs"][op["airliner_msg"]]["operational_names"].iteritems():
                            if op_name == op_attr:
                                return op_data["field_path"]
  
        return None

    def __proto_obj_factory(self, msg):
        """ Returns a protobuf object for the type of airliner msg passed """
        return pyliner_msgs.proto_msg_map[msg]()

    def __get_pb_encode_obj(self, cmd, op):
        """ Generates protobuf object from user script command
        
        Args:
            cmd(dict): User command specifying op and args
            op(dict): Operation dict
            
        Returns:
            Protobuf object for this specific message with set values
        """
        # Check if no args cmd
        if len(op["airliner_msg"]) == 0:
            return None
        
        # Call the correct protobuf constructor for this command
        pb_obj = self.__proto_obj_factory(op["airliner_msg"])
        
        # Generate executable string assigning correct values to pb object
        assign = ""
        for arg in cmd["args"]:
            arg_path =  self._get_op_attr(cmd["name"], arg["name"])
            if not arg_path:
                raise InvalidCommand("Invalid command received. Argument operational name (%s) not found." % arg["name"])
            assign += ("pb_obj." + arg_path + "=" + str(arg["value"]) + "\n")
        exec(assign)
        
        return pb_obj
        
    def __get_pb_decode_obj(self, raw_tlm, op_path):
        """ Generates protobuf object from raw telemetry
        
        Args:
            raw_tlm(str): Raw bytes received from socket
            op_path(str): Operation path as located in input file (E.g. "/Airliner/ES/Noop")
            
        Returns:
            Protobuf object for this specific message with set values
        """
        op = self.__get_airliner_op(op_path)
        if not op:
            return None
        
        # Check if no args cmd
        if len(op["airliner_msg"]) == 0:
            return None
        
        # Call the correct protobuf constructor for this command
        pb_msg = self.__proto_obj_factory(op["airliner_msg"])
        pb_msg.ParseFromString(raw_tlm)
        
        return pb_msg

    def send_command(self, cmd):
        """ User accessible function to send a command to the software bus. 
        
        Args:
            cmd(dict): A command specifiying the operation to execute and any args for it.
                       E.g.    {'name':'/Airliner/ES/Noop'} 
                                    or
                               {'name':'/Airliner/PX4/ManualControlSetpoint', 'args':[
                                   {'name':'X', 'value':'0'},
                                   {'name':'Y', 'value':'0'},
                                   {'name':'Z', 'value':'500'}]}
        """
        args_present = False
        
        if "name" not in cmd:
            raise InvalidCommand("Invalid command received. Missing \"name\" attribute")
        
        # Check if no args cmd
        if "args" in cmd:
            args_present = True

        # Get command operation        
        op = self.__get_airliner_op(cmd["name"])
        if not op:
            raise InvalidCommand("Invalid command received. Operation (%s) not defined." % cmd["name"])

        # Generate airliner cmd
        header = self.__get_ccsds_msg(op)
        payload = self.__get_pb_encode_obj(cmd, op) if args_present else None
        
        # Set header correctly
        payload_size = payload.ByteSize() if args_present else 0
        header.set_user_data_length(payload_size)
        payload_checksum = payload.SerializeToString() if args_present else 0
        header.SecHdr.Command.bits.checksum = header.compute_checksum(payload_checksum) if args_present else 0
        
        serial_cmd = self.serialize(header, payload)      
        self.send_to_airliner(serial_cmd)

    def __get_pb_value(self, pb_msg, op_path, op_attr):
        """ Get value from protobuf object
        
        Args:
            pb_msg(ProtoObj): Protobuf object for this message
            op_path(str): Operation path as located in input file (E.g. "/Airliner/ES/Noop")
            op_attr(str): Operational name of message attribute (E.g. CmdCounter)
            
        Returns:
            Value of attribute for passed proto message
        """
        value = None
        arg_path =  self._get_op_attr(op_path, op_attr)
        if not arg_path:
            return None
        assign_string = "value =  pb_msg." + arg_path
        exec(assign_string)
        return value

    def __on_recv_telemetry(self, tlm):
        """ Callback for TO socket listener 
        
        Args:
            tlm(str): Raw bytes received from socket
        """
        if not self.ingest_active:
            return
        
        self.all_telemetry.append(tlm)
        #logging.debug("Recvd tlm: " + str(tlm))
        
        # TODO: Check if needed
        hdr = tlm[0].split()[0][:12]
        if len(hdr) < 12:
            print "header length: " + str(len(hdr))
            print self.request[0].split()
        
        # Get python CCSDS object #TODO: Check what causes this to fail on some tlm pkts
        try: 
            header = bytearray(hdr)
            tlm_pkt = CCSDS_TlmPkt_t()
            tlm_pkt.set_decoded(header)
            tlm_time = tlm_pkt.get_time()
        except Exception as e:
            print e

        # Iterate over subscribed telemetry to check if we care
        for subscribed_tlm in self.subscribers:
            if int(subscribed_tlm['airliner_mid'], 0) == int(tlm_pkt.PriHdr.StreamId.data):
                if subscribed_tlm['callback']:
                    # Get pb msg for this msg
                    pb_msg = self.__get_pb_decode_obj(tlm[0][12:], subscribed_tlm['op_path'])

                    # Generate telemtry dictionary for callback
                    cb_dict = {}
                    cb_dict['name'] = subscribed_tlm['op_path']
                    cb_dict['params'] = {}
                    for op in [op['name'] for op in subscribed_tlm['params']]:
                        cb_dict['params'][op] = {}
                        cb_dict['params'][op]['value'] = self.__get_pb_value(pb_msg, cb_dict['name'], op)
                        cb_dict['params'][op]['time'] = tlm_time
                    
                    # Call specified callback for this telemetry
                    subscribed_tlm['callback'](cb_dict)
            
    def subscribe(self, tlm, callback=None):
        """ Receives an operation path to an airliner msg with ops names of that 
        messages attributes to subscribe to as well as a callback function.

        Args:
            tlm(dict): Dictionary specifying the telemtry items to subscribe to, using the 
                       telemtry item's operational names. 
                       E.g. {'name': '/Airliner/ES/HK', 'args':[
                                {'name':'CmdCounter'}]}

            callback(function): Function to call when this telemetry is updated. If not specified
                                defaults to on_recv_telemetry                                
        """
        # Get operation for specified telemetry
        op = self.__get_airliner_op(tlm["name"])
        if not op:
            raise InvalidCommand("Invalid command received. Operation (%s) not defined." % cmd["name"])
        
        # Add entry to subscribers list
        self.subscribers.append({'op_path': tlm["name"],
                                 'airliner_mid': op['airliner_mid'],
                                 'params':tlm['args'], 
                                 'callback':callback,
                                 'tlmSeqNum': 0})

    def step_frame(self, steps = 1):
        """ Step passed number of frames """
        pass
        
    def step_forever(self):
        """ Run Airliner at max speed """
        pass
        
    def pause_frame(self):
        """ Stop Airliner execution """
        pass

    def send_to_airliner(self, msg):
        """ Publish the passed message to airliner """
        self.ci_socket.sendto(msg, (self.address, self.ci_port))
    
    def recv_telemetry(self):
        """ 
        Listen to the the socket TO is publishing to. If it receives telemetry 
        we're subscribed to notify the correct callback.
        """
        self.listener_thread.daemon = True
        self.listener_thread.start()
        
    def reset_test(self):
        """ Reset  """
        pass #Need this?
        
    def assert_equals(self, a, b):
        """ Assert for Pyliner that tracks passes and failures """
        if a == b:
            self.passes += 1
            logging.info('Valid assertion made: %s == %s' % (a, b))
        else:
            self.fails += 1
            logging.warn('Invalid assertion made: %s == %s' % (a, b))
            
    def assert_not_equals(self, a, b):
        """ Assert for Pyliner that tracks passes and failures """
        if a != b:
            self.passes += 1
            logging.info('Valid assertion made: %s != %s' % (a, b))
        else:
            self.fails += 1
            logging.warn('Invalid assertion made: %s != %s' % (a, b))
            
    def assert_true(self, expr):
        """ Assert for Pyliner that tracks passes and failures """
        if expr:
            self.passes += 1
            logging.info("Valid true assertion made")
        else:
            self.fails += 1
            logging.warn("Invalid true assertion made")
            
    def assert_false(self, expr):
        """ Assert for Pyliner that tracks passes and failures """
        if not expr:
            self.passes += 1
            logging.info("Valid false assertion made")
        else:
            self.fails += 1
            logging.warn("Invalid false assertion made")

    def dump_tlm(self):
        """ Dump all received telemetry to file """
        with open(join(self.log_dir, self.log_name[:-3]) + 'tlm', 'w') as tlm_file:
            for tlm in self.all_telemetry:
                tlm_file.write(str(tlm) + '\n')
            
    def get_test_results(self):
        """ Generates a string with all test results """
        time_diff = datetime.now() - self.start_time
        diff = divmod(time_diff.total_seconds(), 60)
        duration = "%i minutes %i seconds"%(diff[0],diff[1]) if diff[0] > 0 else "%i seconds"%(diff[1])
        result = "PASS" if self.fails == 0 else "FAIL"

        results = "\n=================================================\n"
        results += "Pyliner test complete\n\n"
        results += "Test case:  " + self.test_name + "\n"
        results += "Result:     " + result + "\n"
        results += "Passes:     " + str(self.passes) + "\n"
        results += "Fails:      " + str(self.fails) + "\n"
        results += "Duration:   " + str(duration) + "\n"
        results += "================================================="
        return results

    def finish_test(self):
        """ Do all the clean up post test execution """
        self.ingest_active = False
        self.dump_tlm()
        print self.get_test_results()


class ThreadedUDPRequestHandler(SocketServer.BaseRequestHandler):

    def __init__(self, callback, *args, **keys):
        self.callback = callback
        SocketServer.BaseRequestHandler.__init__(self, *args, **keys)
        
    def handle(self):
        self.callback(self.request)


