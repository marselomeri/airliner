#!/usr/bin/python

import SocketServer
import logging
import threading
import time
from datetime import datetime
from os import mkdir
from os.path import exists, join, dirname, realpath

from junit_xml import TestSuite, TestCase
from deprecated import deprecated

import exceptions
import python_pb.pyliner_msgs as pyliner_msgs
from arte_ccsds import CCSDS_TlmPkt_t, CCSDS_CmdPkt_t
from flight_control_lib import FlightMode
from pyliner_module import PylinerModule
from util import init_socket, server_factory, read_json, serialize, LogLevel

DEFAULT_CI_PORT = 5008
DEFAULT_TO_PORT = 5011


class Pyliner(object):
    """A Pyliner object represents a vehicle that the user may control.
    """
    def __init__(self, address='localhost', ci_port=DEFAULT_CI_PORT,
                 to_port=DEFAULT_TO_PORT, script_name=None, airliner_map=None,
                 log_dir=None):
        if airliner_map is None:
            airliner_map = join(dirname(realpath(__file__)), "airliner.json")
        if log_dir is None:
            log_dir = join(dirname(realpath(__file__)), "logs")

        self.address = address
        self.airliner_data = read_json(airliner_map)
        self.all_telemetry = []
        self.ci_port = ci_port
        self.ci_socket = init_socket()
        self.duration = 0
        self.fails = 0
        self.ingest_active = True
        self.passes = 0
        self.subscribers = []
        self.telemetry = {}
        self.test_description = []
        self.to_port = to_port
        self.to_socket = init_socket()

        # Threading
        self.tlm_listener = SocketServer.UDPServer(
            ("0.0.0.0", self.to_port), server_factory(self._on_recv_telemetry))
        self.listener_thread = threading.Thread(
            target=self.tlm_listener.serve_forever)

        # Logging
        self.log_dir = log_dir
        self.script_name = script_name
        self.start_time = datetime.now()
        self.log_name = self.start_time.strftime("%Y-%m-%d_%I:%M:%S") + \
                        "_pyliner_" + self.script_name + ".log"
        self._setup_log()

        # Start Telemetry
        self.listener_thread.daemon = True
        self.listener_thread.start()

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        if exc_type:
            print(exc_type, exc_val, exc_tb)
            print('Error in execution. Returning to Launch')
            self.rtl()
            self.wait_clean()

    def wait_clean(self):
        while self.send_dirty:
            time.sleep(1 / 32)

    def arm(self):
        print("%s: Arming vehicle" % self.script_name)
        self.log("Arming vehicle")
        self.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.0},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 0},
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 0},
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 0},
                 {'name': 'GearSwitch', 'value': 0},
                 {'name': 'ArmSwitch', 'value': 3},  # OFF
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})
        self.wait_clean()
        self.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.0},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 0},
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 0},
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 0},
                 {'name': 'GearSwitch', 'value': 0},
                 {'name': 'ArmSwitch', 'value': 1},  # ON
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})
        self.wait_clean()

    def atp(self, txt):
        print("%s requires authorization for: %s" % (self.script_name, txt))
        raw_input("Press enter to proceed >>>")
        self.log("%s requires authorization to proceed. Requesting: %s" % (
            self.script_name, txt))

    def await_fresh(self, tlm, poll=1, out=None):
        """Loop until the telemetry value changes. This is blocking.

        Args:
            tlm (str): The telemetry to monitor.
            poll (float): Check every `poll` seconds.
            out (Any): If not None, print this every loop.
        """
        old_val = self.tlm_value(tlm)
        while self.tlm_value(tlm) == old_val:
            if out is not None:
                print(out)
            time.sleep(poll)

    def disable_module(self, name):
        """Disable a module. Does not unsubscribe from any telemetry."""
        if isinstance(getattr(self, name, None), PylinerModule):
            delattr(self, name)
        else:
            raise AttributeError('Cannot disable a module that was never '
                                 'enabled.')

    def enable_module(self, name, module):
        """
        Enable a Pyliner Module on this vehicle. All required telemetry for the
        new module will be subscribed to.

        Args:
            name (str): The name that the module will be initialized under.
            module (Type[PylinerModule]): The module to enable.
        """
        if not issubclass(module, PylinerModule):
            return TypeError('module must implement PylinerModule.')
        if not hasattr(self, name):
            self.subscribe({'tlm': module.required_telemetry_paths()})
            setattr(self, name, module(self))
        else:
            raise ValueError('Attempting to enable a module on top of an '
                             'existing variable or module.')

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
            op_path (str): Operation path as located in input file (E.g. "/Airliner/ES/Noop")

        Returns:
            True path to access this attribute in protobuf message (E.g. Payload.CmdCounter)
        """
        op = self._get_airliner_op(op_path)
        ops_names = op_path.split('/')[1:]
        for fsw, fsw_data in self.airliner_data.iteritems():
            if fsw == ops_names[0]:
                for app, app_data in fsw_data["apps"].iteritems():
                    if app_data["app_ops_name"] == ops_names[1]:
                        for op_name, op_data in app_data["proto_msgs"][op["airliner_msg"]][
                            "operational_names"].iteritems():
                            if op_name == ops_names[3]:
                                return op_data["field_path"]

        return None

    def _get_pb_decode_obj(self, raw_tlm, op_path):
        """ Generates protobuf object from raw telemetry

        Args:
            raw_tlm (str): Raw bytes received from socket
            op_path (str): Operation path as located in input file (E.g. "/Airliner/ES/Noop")

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
        exec (assign)

        return pb_obj

    def _get_pb_value(self, pb_msg, op_path):
        """ Get value from protobuf object

        Args:
            pb_msg (ProtoObj): Protobuf object for this message
            op_path (str): Operation path as located in input file (E.g. "/Airliner/ES/Noop")

        Returns:
            Value of attribute for passed proto message
        """
        value = None
        arg_path = self._get_op_attr(op_path)
        if not arg_path:
            return None
        assign_string = "value =  pb_msg." + arg_path
        exec (assign_string)
        return value

    def flight_mode(self, mode):
        if not mode:
            self.log("Mode transition requires a passed mode.",
                         LogLevel.Error)
        if mode == FlightMode.Manual:
            raise NotImplemented()
        elif mode == FlightMode.AltCtl:
            raise NotImplemented()
        elif mode == FlightMode.PosCtl:
            self.mode_posctl()
        self.wait_clean()

    def mode_posctl(self):
        print "%s: Position control" % self.script_name
        self.log("Position control")
        self.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.5},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 0},
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 1},  # ON
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 0},
                 {'name': 'GearSwitch', 'value': 1},
                 {'name': 'ArmSwitch', 'value': 0},
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})

    def takeoff(self):
        print("%s: Auto takeoff" % self.script_name)
        self.log("Auto takeoff")
        self.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                 {'name': 'Timestamp', 'value': get_time()},
                 {'name': 'X', 'value': 0.0},
                 {'name': 'Y', 'value': 0.0},
                 {'name': 'Z', 'value': 0.0},
                 {'name': 'R', 'value': 0.0},
                 {'name': 'Flaps', 'value': 0.0},
                 {'name': 'Aux1', 'value': 0.0},
                 {'name': 'Aux2', 'value': 0.0},
                 {'name': 'Aux3', 'value': 0.0},
                 {'name': 'Aux4', 'value': 0.0},
                 {'name': 'Aux5', 'value': 0.0},
                 {'name': 'ModeSwitch', 'value': 0},
                 {'name': 'ReturnSwitch', 'value': 0},
                 {'name': 'RattitudeSwitch', 'value': 0},
                 {'name': 'PosctlSwitch', 'value': 0},
                 {'name': 'LoiterSwitch', 'value': 0},
                 {'name': 'AcroSwitch', 'value': 0},
                 {'name': 'OffboardSwitch', 'value': 0},
                 {'name': 'KillSwitch', 'value': 0},
                 {'name': 'TransitionSwitch', 'value': 1},  # ON
                 {'name': 'GearSwitch', 'value': 0},
                 {'name': 'ArmSwitch', 'value': 1},
                 {'name': 'StabSwitch', 'value': 0},
                 {'name': 'ManSwitch', 'value': 0},
                 {'name': 'ModeSlot', 'value': 0},
                 {'name': 'DataSource', 'value': 0}]})
        time.sleep(5)

    def tlm(self, tlm):
        """ Get all data of specified telemetry item

        Args:
            tlm (str): Operational name of requested telemetry

        Returns:
            Telemetry data dict or None if not found
        """
        if tlm not in self.telemetry:
            return None
        else:
            return self.telemetry[tlm]

    def tlm_value(self, tlm):
        """ Get current value of specified telemetry item

        Args:
            tlm (str): Operational name of requested telemetry

        Returns:
            Current value of telemetry or None if not found
        """
        if tlm not in self.telemetry:
            return None
        else:
            return self.telemetry[tlm]['value']

    def rtl(self):
        print("%s: RTL" % self.script_name)
        self.log("RTL")
        self.send_telemetry(
            {'name': '/Airliner/CNTL/ManualSetpoint',
             'args': [
                {'name': 'Timestamp', 'value': get_time()},
                {'name': 'X', 'value': 0.0},
                {'name': 'Y', 'value': 0.0},
                {'name': 'Z', 'value': 0.0},
                {'name': 'R', 'value': 0.0},
                {'name': 'Flaps', 'value': 0.0},
                {'name': 'Aux1', 'value': 0.0},
                {'name': 'Aux2', 'value': 0.0},
                {'name': 'Aux3', 'value': 0.0},
                {'name': 'Aux4', 'value': 0.0},
                {'name': 'Aux5', 'value': 0.0},
                {'name': 'ModeSwitch', 'value': 0},
                {'name': 'ReturnSwitch', 'value': 1},  # ON
                {'name': 'RattitudeSwitch', 'value': 0},
                {'name': 'PosctlSwitch', 'value': 0},
                {'name': 'LoiterSwitch', 'value': 0},
                {'name': 'AcroSwitch', 'value': 0},
                {'name': 'OffboardSwitch', 'value': 0},
                {'name': 'KillSwitch', 'value': 0},
                {'name': 'TransitionSwitch', 'value': 0},
                {'name': 'GearSwitch', 'value': 3},
                {'name': 'ArmSwitch', 'value': 1},
                {'name': 'StabSwitch', 'value': 0},
                {'name': 'ManSwitch', 'value': 0},
                {'name': 'ModeSlot', 'value': 0},
                {'name': 'DataSource', 'value': 0}]})

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
        args_present = False

        if "name" not in cmd:
            raise exceptions.InvalidCommandException("Invalid command received. Missing \"name\" attribute")

        # Check if no args cmd
        args_present = "args" in cmd

        # Get command operation
        op = self._get_airliner_op(cmd["name"])
        if not op:
            raise exceptions.InvalidCommandException("Invalid command received. Operation (%s) not defined." % cmd["name"])

        # Generate airliner cmd
        header = self._get_ccsds_msg(op)
        payload = self._get_pb_encode_obj(cmd, op) if args_present else None

        # Set header correctly
        payload_size = payload.ByteSize() if args_present else 0
        header.set_user_data_length(payload_size)
        payload_checksum = payload.SerializeToString() if args_present else 0
        header.SecHdr.Command.bits.checksum = header.compute_checksum(payload_checksum) if args_present else 0

        serial_cmd = serialize(header, payload)
        self.send_to_airliner(serial_cmd)
        self.log('Sending command to airliner: %s' % (cmd))

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
            raise exceptions.InvalidCommandException("Invalid command received. Missing \"name\" attribute")

        # Check if no args tlm
        args_present = "args" in tlm

        # Get command operation
        op = self._get_airliner_op(tlm["name"])
        if not op:
            raise exceptions.InvalidCommandException("Invalid telemetry received. Operation (%s) not defined." % tlm["name"])

        # Generate airliner cmd
        header = self._get_ccsds_msg(op)
        payload = self._get_pb_encode_obj(tlm, op) if args_present else None

        # Set header correctly
        payload_size = payload.ByteSize() if args_present else 0
        header.set_user_data_length(payload_size)

        serial_cmd = serialize(header, payload)
        self.msg = serial_cmd
        self.send_dirty = True
        self.log('Sending telemetry to airliner: %s' % tlm)
        # header.print_base10()

    def send_to_airliner(self, msg):
        """ Publish the passed message to airliner """
        self.ci_socket.sendto(msg, (self.address, self.ci_port))

    def _setup_log(self):
        """ Setup log for Pyliner """
        if not exists(self.log_dir):
            mkdir(self.log_dir)

        logging.basicConfig(format='%(asctime)s\t%(levelname)s: %(message)s',
                            datefmt='%m/%d/%Y %I:%M:%S %p',
                            filename=join(self.log_dir, self.log_name),
                            level=logging.DEBUG)

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
                updated. If not specified defaults to on_recv_telemetry.
        """
        for tlm_item in tlm["tlm"]:
            # Get operation for specified telemetry
            op = self._get_airliner_op(tlm_item)
            if not op:
                err_msg = "Invalid telemetry operational name received. Operation (%s) not defined." % tlm_item
                self.log(err_msg, LogLevel.Error)
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

            self.log('Subscribing to the following telemetry: %s' % (tlm))

    # Testing Code. TODO Figure out where to put this
    def reset_test(self):
        """ Reset  """
        pass  # Need this?

    def assert_equals(self, a, b, description):
        """ Assert for Pyliner that tracks passes and failures """
        if a == b:
            self.passes += 1
            self.log('Valid assertion made: %s == %s' % (a, b))
        else:
            self.fails += 1
            self.log('Invalid assertion made: %s == %s' % (a, b), LogLevel.Warn)

    def assert_not_equals(self, a, b, description, result):
        """ Assert for Pyliner that tracks passes and failures """
        if a != b:
            self.passes += 1
            self.test_description.append(description)
            self.log('Valid assertion made: %s != %s' % (a, b))

        else:
            self.fails += 1
            self.test_description.append(description)
            self.log('Invalid assertion made: %s != %s' % (a, b), LogLevel.Warn)

    def assert_true(self, expr, description):
        """ Assert for Pyliner that tracks passes and failures """
        if expr:
            self.passes += 1
            self.test_description.append(description)
            self.log("Valid true assertion made")
        else:
            self.fails += 1
            self.test_description.append(description)
            self.log("Invalid true assertion made", LogLevel.Warn)

    def assert_false(self, expr, description):
        """ Assert for Pyliner that tracks passes and failures """
        if not expr:
            self.passes += 1
            self.test_description.append(description)
            self.log("Valid false assertion made")
        else:
            self.fails += 1
            self.test_description.append(description)
            self.log("Invalid false assertion made", LogLevel.Warn)

    def dump_tlm(self):
        """ Dump all received telemetry to file """
        with open(join(self.log_dir, self.log_name[:-3]) + 'tlm', 'w') as tlm_file:
            for tlm in self.all_telemetry:
                tlm_file.write(str(tlm) + '\n')

    def get_test_results(self):
        """ Generates a string with all test results """
        time_diff = datetime.now() - self.start_time
        diff = divmod(time_diff.total_seconds(), 60)
        duration = "%i minutes %i seconds" % (diff[0], diff[1]) if diff[0] > 0 else "%i seconds" % (diff[1])
        self.duration = time_diff.seconds
        result = "PASS" if self.fails == 0 else "FAIL"

        results = "=================================================\n"
        results += "Pyliner test complete\n"
        results += "Test case:  " + self.script_name + "\n"
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
        self.generate_junit()

    def log(self, text, level=LogLevel.Info):
        """ Wrapper for logging function """
        if level == LogLevel.Debug:
            logging.debug(text)
        elif level == LogLevel.Info:
            logging.info(text)
        elif level == LogLevel.Warn:
            logging.warn(text)
        elif level == LogLevel.Error:
            logging.error(text)
        else:
            logging.debug("Specified log mode unsupported")

    def generate_junit(self):
        # Get the test count
        test_count = self.passes + self.fails
        # Add the first test case
        test_cases = [TestCase(self.script_name + str(0), '', self.duration / test_count, '', '')]
        # Add the remaining test cases
        for x in range(1, test_count):
            test_cases.append(TestCase(self.script_name + str(x), '', self.duration / test_count, '', ''))
        # Add any failure info
        for x in range(0, self.fails):
            test_cases[0].add_failure_info(self.test_description[x])
        ts = TestSuite("test suite", test_cases)
        with open(join(self.log_dir, self.script_name + '_results.xml'), 'w') as f:
            TestSuite.to_file(f, [ts], prettyprint=False)
