import json
import logging
import socket
import sys
import threading
import time
import traceback
from collections import Iterator, Iterable
from datetime import datetime

import socketserver
from flufl.enum import Enum


class EventType(Enum):
    CONSOLE_OUT = 'CONSOLE_OUT'
    CONSOLE_IN = 'CONSOLE_IN'
    LOG = 'LOG'


class Event(object):
    def __init__(self, type):
        self.type = type


class Log(object):
    """Reflects Android's util.Log class"""
    def __init__(self, log_file, level):
        self.fails = 0
        self.passes = 0
        self.duration = 0
        self.test_description = []

        self.log_file = log_file
        logging.basicConfig(format='%(asctime)s\t%(levelname)s: %(message)s',
                            datefmt='%m/%d/%Y %I:%M:%S %p',
                            filename=log_file,
                            level=level)


class PeriodicExecutor(threading.Thread):
    """Executes a callback function every x-seconds.

    Optionally takes callbacks for exception and last-pass handling.
    """

    def __init__(self, callback, every=1, exception=None, finalize=None):
        """
        Args:
            callback (Callable): This method will be called every loop
                with no arguments.
            every (Real): Number of seconds to sleep between calls.
            exception (Callable): If an exception is raised this will
                be called with the exception as an argument.
            finalize (Callable): This method will be called sometime
                after the thread is stopped with no arguments.
        """
        super(PeriodicExecutor, self).__init__()
        self.daemon = True

        self.callback = callback
        # TODO if move to Python 3, use lambda x: print(x)
        self.exception = exception
        self.every = every
        self.finalize = finalize
        self.running = False

    def run(self):
        """Do not call this directly. Use PeriodicExecutor.start()"""
        self.running = True
        try:
            while self.running:
                self.callback()
                time.sleep(self.every)
        except Exception as e:
            if callable(self.exception):
                self.exception(e)
            else:
                print('\nException in thread {}'.format(self.callback))
                traceback.print_exc()
        finally:
            if callable(self.finalize):
                self.finalize()

    def stop(self):
        """Stops the thread from continuing to loop.

        Thread will not stop immediately. When the thread wakes up next it will
        see that it has been stopped, will execute the finalize method if it was
        given, and will then complete.
        """
        if self.running:
            self.running = False
        else:
            raise RuntimeError('This thread cannot be stopped now.')


class ThreadedUDPRequestHandler(socketserver.BaseRequestHandler):
    def __init__(self, callback, *args, **keys):
        self.callback = callback
        socketserver.BaseRequestHandler.__init__(self, *args, **keys)

    def handle(self):
        self.callback(self.request)


def shifter(num, iterator):
    if not isinstance(iterator, Iterator) \
            and isinstance(iterator, Iterable):
        iterator = iter(iterator)
    output = tuple(next(iterator) for _ in range(num))
    yield output
    for item in iterator:
        output = tuple(output[index+1] if index < num-1 else item
                       for index in range(num))
        yield output


def feet(ft):
    """Convert from given feet to meters."""
    return ft * 0.3048


def get_time():
    return int(
        (datetime.utcnow() - datetime(1970, 1, 1)).total_seconds() * 10000)


def handler_factory(callback):
    """ Creates server object and sets the callback """
    return lambda *args, **kwargs: ThreadedUDPRequestHandler(callback, *args,
                                                             **kwargs)


def indent(level, iterable):
    for string in iterable:
        yield ' ' * level + str(string)


def init_socket():
    """ Creates a UDP socket object and returns it """
    return socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


def query_yes_no(question, default=None, **extra):
    """Ask a yes/no question via raw_input() and return their answer.

    "question" is a string that is presented to the user.
    "default" is the presumed answer if the user just hits <Enter>.

    The "answer" return value is one of "yes" or "no".
    Adapted from: http://code.activestate.com/recipes/577058/
    """
    valid = {True: {'y', 'ye', 'yes'},
             False: {'n', 'no'}}
    valid.update(extra)
    if default is None:
        prompt = " [y/n] "
    elif default:
        prompt = " [Y/n] "
    else:
        prompt = " [y/N] "

    while True:
        sys.stdout.write(question + prompt)
        choice = raw_input().lower()
        if default is not None and choice == '':
            return default
        for answer, options in valid.items():
            if choice in options:
                return answer
        else:
            sys.stdout.write("Please respond with 'yes' or 'no' "
                             "(or 'y' or 'n').\n")


def read_json(file_path):
    """Parses the required JSON input file containing Airliner mappings.

    Returns:
        dict
    """
    try:
        with open(file_path, 'r') as airliner_map:
            return json.load(airliner_map)
    except IOError:
        print("Specified input file (%s) does not exist" % file_path)
    except Exception as e:
        print(e)


def serialize(header, payload):
    """
    Receive a CCSDS message and payload then returns the
    serialized concatenation of them.
    """
    ser = header.get_encoded()
    if payload:
        ser += payload.SerializeToString()
    return ser
