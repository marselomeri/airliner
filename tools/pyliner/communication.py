import SocketServer
import threading
from os.path import join, dirname, realpath
import time

from deprecated import deprecated

import exceptions
from arte_ccsds import CCSDS_TlmPkt_t, CCSDS_CmdPkt_t
from pyliner_module import PylinerModule
from python_pb import pyliner_msgs
from util import read_json, init_socket, PeriodicExecutor, server_factory, \
    LogLevel, serialize

DEFAULT_CI_PORT = 5008
DEFAULT_TO_PORT = 5011


class Communication(PylinerModule):
    """Provide methods to send and receive telemetry to a vehicle."""
    def __init__(self, address='localhost', ci_port=DEFAULT_CI_PORT,
                 to_port=DEFAULT_TO_PORT, airliner_map=None):
        super(Communication, self).__init__()

        if airliner_map is None:
            airliner_map = join(dirname(realpath(__file__)), "airliner.json")
        self.airliner_data = read_json(airliner_map)
        if self.airliner_data is None:
            raise ValueError('There was a problem reading Airliner data at '
                             '{}'.format(airliner_map))

        # Telemetry variables
        self.address = address
        self.all_telemetry = []
        self.ci_port = ci_port
        self.ci_socket = init_socket()
        self.msg = None
        self.send_dirty = True
        self.telemetry = {}
        self.subscribers = []
        self.to_port = to_port
        self.to_socket = init_socket()

        # Receive Telemetry
        self.tlm_listener = SocketServer.UDPServer(
            ("0.0.0.0", self.to_port), server_factory(self._on_recv_telemetry))
        self.listener_thread = threading.Thread(
            target=self.tlm_listener.serve_forever)
        self.listener_thread.daemon = True
        self.listener_thread.start()

        # Send Telemetry
        def callback():
            # print('Sending')
            self.send_to_airliner()
            self.send_dirty = False

        self.periodic_send = PeriodicExecutor(callback, every=1)
        self.periodic_send.start()

    def _get_airliner_op(self, op_path):
        """
        Receive a ops path and returns the dict for that op defined in
        the input file
        """
        ret_op = None
        ops_names = op_path.split('/')[1:]

        for fsw, fsw_data in self.airliner_data.iteritems():
            if fsw == ops_names[0]:
                for app, app_data in fsw_data["apps"].iteritems():
                    if app_data["app_ops_name"] == ops_names[1]:
                        op = app_data["operations"][ops_names[2]]
                        ret_op = op if op else None
        return ret_op

    def _get_ccsds_msg(self, op):
        """ Receive a ops dict and returns a ccsds msg """
        # If the command code is -1 this is telemetry
        if op["airliner_cc"] == -1:
            ret_msg = CCSDS_TlmPkt_t()
            ret_msg.clear_packet()
            ret_msg.init_packet()
            ret_msg.PriHdr.StreamId.bits.app_id = int(op["airliner_mid"], 0)
        else:
            ret_msg = CCSDS_CmdPkt_t()
            ret_msg.clear_packet()
            ret_msg.init_packet()
            ret_msg.PriHdr.StreamId.bits.app_id = int(op["airliner_mid"], 0)
            ret_msg.SecHdr.Command.bits.code = int(op["airliner_cc"])
        return ret_msg

    def _get_op_attr(self, op_path):
        """ Gets the operation path from airliner data for a specified attribute

        Args:
            op_path (str): Operation path as located in input file
                (E.g. "/Airliner/ES/Noop")

        Returns:
            True path to access this attribute in protobuf message
                (E.g. Payload.CmdCounter)
        """
        op = self._get_airliner_op(op_path)
        ops_names = op_path.split('/')[1:]
        for fsw, fsw_data in self.airliner_data.iteritems():
            if fsw == ops_names[0]:
                for app, app_data in fsw_data["apps"].iteritems():
                    if app_data["app_ops_name"] == ops_names[1]:
                        for op_name, op_data in app_data["proto_msgs"] \
                                [op["airliner_msg"]] \
                                ["operational_names"].iteritems():
                            if op_name == ops_names[3]:
                                return op_data["field_path"]
        return None

    def _get_pb_decode_obj(self, raw_tlm, op_path):
        """ Generates protobuf object from raw telemetry

        Args:
            raw_tlm (str): Raw bytes received from socket
            op_path (str): Operation path as located in input file
                (E.g. "/Airliner/ES/Noop")

        Returns:
            Protobuf object for this specific message with set values
        """
        op = self._get_airliner_op(op_path)
        if not op:
            return None

        # Check if no args cmd
        if len(op["airliner_msg"]) == 0:
            return None

        # Call the correct protobuf constructor for this command
        pb_msg = self._proto_obj_factory(op["airliner_msg"])
        pb_msg.ParseFromString(raw_tlm)
        return pb_msg

    def _get_pb_encode_obj(self, cmd, op):
        """ Generates protobuf object from user script command

        Args:
            cmd (dict): User command specifying op and args
            op (dict): Operation dictionary

        Returns:
            Protobuf object for this specific message with set values
        """
        # Check if no args cmd
        if len(op["airliner_msg"]) == 0:
            return None

        # Call the correct protobuf constructor for this command
        pb_obj = self._proto_obj_factory(op["airliner_msg"])

        # Generate executable string assigning correct values to pb object
        assign = ""
        for arg in cmd["args"]:
            arg_path = self._get_op_attr(cmd["name"] + '/' + arg["name"])
            if not arg_path:
                raise exceptions.InvalidCommandException(
                    "Invalid command received. Argument operational name (%s) not found." % arg["name"])
            assign += ("pb_obj." + arg_path + "=" + str(arg["value"]) + "\n")
        exec assign
        return pb_obj

    def _get_pb_value(self, pb_msg, op_path):
        """ Get value from protobuf object

        Args:
            pb_msg (ProtoObj): Protobuf object for this message
            op_path (str): Operation path as located in input file
                (E.g. "/Airliner/ES/Noop")

        Returns:
            Value of attribute for passed proto message
        """
        arg_path = self._get_op_attr(op_path)
        if not arg_path:
            return None
        value = getattr(pb_msg, arg_path)
        return value

    def _on_recv_telemetry(self, tlm):
        """ Callback for TO socket listener

        Args:
            tlm(str): Raw bytes received from socket
        """
        self.all_telemetry.append(tlm)
        # self.log("Recvd tlm: " + str(tlm), LogLevel.Debug)

        # TODO: Check if needed
        hdr = tlm[0][:12]
        if len(hdr) < 12:
            self.vehicle.log("Rcvd tlm with header length: " + str(len(hdr)),
                             LogLevel.Debug)
            # print "Rcvd tlm with header length: " + str(len(hdr))

        # Get python CCSDS object
        # TODO: Check what causes this to fail on some tlm packets
        try:
            header = bytearray(hdr)
            tlm_pkt = CCSDS_TlmPkt_t()
            tlm_pkt.set_decoded(header)
            tlm_time = tlm_pkt.get_time()
        except Exception as e:
            self.vehicle.log("Exception when decoding tlm in ccsds: {}"
                             .format(e), LogLevel.Debug)
            print(e)
            return

        # Iterate over subscribed telemetry to check if we care
        for subscribed_tlm in self.subscribers:
            if int(subscribed_tlm['airliner_mid'], 0) == int(
                    tlm_pkt.PriHdr.StreamId.data):
                # Get pb msg for this msg
                pb_msg = self._get_pb_decode_obj(tlm[0][12:],
                                                 subscribed_tlm['op_path'])

                # Generate telemtry dictionary for callback
                cb_dict = {}
                cb_dict['name'] = subscribed_tlm['op_path']
                cb_dict['value'] = self._get_pb_value(pb_msg, cb_dict['name'])
                cb_dict['time'] = tlm_time

                # Update telemetry dictionary with fresh data
                self.telemetry[subscribed_tlm['op_path']] = cb_dict

                # Call specified callback for this telemetry if it has one
                if subscribed_tlm['callback']:
                    subscribed_tlm['callback'](cb_dict)

    @staticmethod
    def _proto_obj_factory(msg):
        """ Returns a protobuf object for the type of airliner msg passed """
        return pyliner_msgs.proto_msg_map[msg]()

    @classmethod
    def required_telemetry_paths(cls):
        return []

    @deprecated
    def send_command(self, cmd):
        """ User accessible function to send a command to the software bus.

        Args:
            cmd (dict): A command specifiying the operation to execute and any args for it.
                       E.g.    {'name':'/Airliner/ES/Noop'}
                                    or
                               {'name':'/Airliner/PX4/ManualControlSetpoint', 'args':[
                                   {'name':'X', 'value':'0'},
                                   {'name':'Y', 'value':'0'},
                                   {'name':'Z', 'value':'500'}]}
        """
        if "name" not in cmd:
            raise exceptions.InvalidCommandException(
                "Invalid command received. Missing \"name\" attribute")

        # Check if no args cmd
        args_present = "args" in cmd

        # Get command operation
        op = self._get_airliner_op(cmd["name"])
        if not op:
            raise exceptions.InvalidCommandException(
                "Invalid command received. Operation (%s) not defined." % cmd[
                    "name"])

        # Generate airliner cmd
        header = self._get_ccsds_msg(op)
        payload = self._get_pb_encode_obj(cmd, op) if args_present else None

        # Set header correctly
        payload_size = payload.ByteSize() if args_present else 0
        header.set_user_data_length(payload_size)
        payload_checksum = payload.SerializeToString() if args_present else 0
        header.SecHdr.Command.bits.checksum = header.compute_checksum(
            payload_checksum) if args_present else 0

        serial_cmd = serialize(header, payload)
        self.send_to_airliner(serial_cmd)
        self.log('Sending command to airliner: %s' % cmd)

    def send_telemetry(self, tlm):
        """ User accessible function to send a command to the software bus.

        Args:
            cmd (dict): A command specifiying the operation to execute and any args for it.
                E.g. {'name':'/Airliner/ES/Noop'}
                    or
                     {'name':'/Airliner/PX4/ManualControlSetpoint',
                      'args':[
                          {'name':'X', 'value':'0'},
                          {'name':'Y', 'value':'0'},
                          {'name':'Z', 'value':'500'}]}
        """
        if "name" not in tlm:
            raise exceptions.InvalidCommandException(
                "Invalid command received. Missing \"name\" attribute")

        # Check if no args tlm
        args_present = "args" in tlm

        # Get command operation
        op = self._get_airliner_op(tlm["name"])
        if not op:
            raise exceptions.InvalidCommandException(
                "Invalid telemetry received. Operation (%s) not defined." % tlm[
                    "name"])

        # Generate airliner cmd
        header = self._get_ccsds_msg(op)
        payload = self._get_pb_encode_obj(tlm, op) if args_present else None

        # Set header correctly
        payload_size = payload.ByteSize() if args_present else 0
        header.set_user_data_length(payload_size)

        serial_cmd = serialize(header, payload)
        self.msg = serial_cmd
        self.send_dirty = True
        self.vehicle.log('Sending telemetry to airliner: %s' % tlm)
        # header.print_base10()

    def send_to_airliner(self):
        """ Publish the passed message to airliner """
        if self.msg is not None:
            # print('Sending {}'.format(round(time.time(), 1)))
            self.ci_socket.sendto(self.msg, (self.address, self.ci_port))

    def subscribe(self, tlm, callback=None):
        """
        Receives an operational path to an airliner msg attribute to subscribe
        to, as well as an optional callback function.

        Args:
            tlm (dict): Dictionary specifying the telemtry items to subscribe
                to, using the telemetry item's operational names.
                E.g. {'tlm': ['/Airliner/ES/HK/CmdCounter']}
                    or
                     {'tlm': ['/Airliner/ES/HK/CmdCounter', '/Airliner/ES/HK/ErrCounter']}

            callback (function): Function to call when this telemetry is
                updated. If not specified defaults to _on_recv_telemetry.
        """
        for tlm_item in tlm["tlm"]:
            # Get operation for specified telemetry
            op = self._get_airliner_op(tlm_item)
            if not op:
                err_msg = "Invalid telemetry operational name received. Operation (%s) not defined." % tlm_item
                self.vehicle.log(err_msg, LogLevel.Error)
                raise exceptions.InvalidOperationException(err_msg)

            # Add entry to subscribers list
            self.subscribers.append({'op_path': tlm_item,
                                     'airliner_mid': op['airliner_mid'],
                                     'callback': callback,
                                     'tlmSeqNum': 0})

            # Add entry to telemetry dictionary to prevent key errors
            # in user scripts and set default values.
            self.telemetry[tlm_item] = {'name': tlm_item,
                                        'value': 'NULL',
                                        'time': 'NULL'}

            self.vehicle.log('Subscribing to the following telemetry: %s' % tlm)
