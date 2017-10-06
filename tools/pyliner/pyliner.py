#!/usr/bin/python

from arte_ccsds import *
import json
from os.path import exists,join
import python_pb.pyliner_msgs as pyliner_msgs
import socket

DEFAULT_CI_PORT = 5009
DEFAULT_TO_PORT = 5012

# Custom exceptions
class InvalidCommand(Exception): pass

class Pyliner(object):

    def __init__(self, **kwargs):
        self.address = kwargs.get("address", "localhost")
        self.ci_port = kwargs.get("ci_port", DEFAULT_CI_PORT)
        self.to_port = kwargs.get("to_port", DEFAULT_TO_PORT)
        self.airliner_data = self.__read_json(kwargs.get("airliner_map", None))
        self.subscribed_tlm = []
        self.ci_socket = self.__init_socket()
        self.to_socket = self.__init_socket()
        self.seq_count = 0

    def __init_socket(self):
        """ Creates a UDP socket object and returns it """
        return socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def __read_json(self, file_path):
        """ Parses the required JSON input file containing Airliner mappings """
        if exists(file_path):
            with open(file_path, 'r') as airliner_map:
                return json.load(airliner_map)
        else:
            raise IOError("Specified input file does not exist")
            
    def __get_airliner_op(self, op_path):
        """ Receive a ops name and returns a dict to that op """
        ret_op = None
        ops_names = op_path.split('/')
        ops_names = ops_names[1:]
        
        for fsw, fsw_data in self.airliner_data.iteritems():
            if fsw == ops_names[0]:
                for app, app_data in fsw_data["apps"].iteritems():
                    if app_data["app_ops_name"] == ops_names[1]:
                        op = app_data["operations"][ops_names[2]]
                        ret_op = op if op else None

        return ret_op

    def __get_ccsds_msg(self, op_dict):
        """ Receive a ops name and returns a ccsds msg """
        # If the command code is -1 this is telemetry
        if op_dict["airliner_cc"] == "-1":
            ret_msg = CCSDS_TlmPkt_t()
            ret_msg.init_packet()
            ret_msg.PriHdr.StreamId.bits.app_id = int(op_dict["airliner_mid"], 0)
        else:
            ret_msg = CCSDS_CmdPkt_t()
            ret_msg.clear_packet()
            ret_msg.init_packet()
            ret_msg.PriHdr.StreamId.bits.app_id = int(op_dict["airliner_mid"], 0)
            ret_msg.SecHdr.Command.bits.code = int(op_dict["airliner_cc"])
        
        return ret_msg

    def serialize(self, header, payload):
        """ Receive a CCSDS message and payload then returns the serialized concatenation of them """
        if not payload:
            return str(header.get_encoded())        
        else:
            return str(header.get_encoded()) + payload.SerializeToString()

    def deserialize(self, msg, msg_id):
        """ Receive the payload of a message and deserializes it """
        tlm_packet = CCSDS_TlmPkt_t()
        tlm_packet.set_decoded(msg[:12]) #TODO
        

    def create_pb_obj(self, cmd, op):
        """ Receives a cmd from the user script and initializes a pb obj of that type. """
        # Check if no args cmd
        if len(op["airliner_msg"]) == 0:
            return None
        
        # Call the correct protobuf constructor for this command
        pb_obj = pyliner_msgs.proto_msg_map[op["airliner_msg"]]()
        
        # Generate executable string assigning correct values to pb object
        assign = ""
        for arg in cmd["args"]:
            assign += ("pb_obj." + arg["name"] + "=" + str(arg["value"]) + "\n")
        exec(assign)
        
        return pb_obj

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
            raise InvalidCommand("Invalid command received. Operation not defined.")

        # Generate airliner cmd
        header = self.__get_ccsds_msg(op)
        payload = self.create_pb_obj(cmd, op) if args_present else None
        
        # Set header correctly
        payload_size = payload.ByteSize() if args_present else 0
        payload_checksum = payload.SerializeToString() if args_present else 0
        header.set_user_data_length(payload_size)
        #header.set_checksum(payload_checksum)
        serial_cmd = self.serialize(header, payload)
        
        self.send_to_airliner(serial_cmd)
        self.seq_count += 1

    def recv_telemetry(self, args):
        """ 
        """
        pass
        
    def step_frame(self, steps = 1):
        """ Step passed number of frames """
        pass

    def send_to_airliner(self, msg):
        """ Publish the passed message to airliner """
        self.ci_socket.sendto(msg, (self.address, self.ci_port))


