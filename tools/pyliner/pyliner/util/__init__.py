"""
The util package contains a lot of random code that doesn't belong anywhere else
yet. If enough code of a similar purpose is added here it should be moved into
its own package or module.

Methods:
    enable_logging  Enable process-wide logging.
    get_time  Get the current time.
    handler_factory  Create a UDP receive handler factory.
    indent  Yield prepended spaces from an iterable.
    init_socket  Create a UDP socket.
    query_yes_no  Ask the user a yes/no question.
    read_json  Read the json from the given file path into a dictionary.
    shifter  Yield an n-tuple of an iterable as it is left-shifted.

Enums:
     EventType  The categories of Events.

Classes:
     Event  An event that is passed around a Vehicle.
     Loggable  Mixin class that provides basic logging methods.
     OverlayDict  Dict where key lookups search multiple dicts.
     PeriodicExecutor  Thread which calls its target periodically.
     LogStream  Intercepts IO to a stream and logs it.
     ThreadedUDPRequestHandler  Sends UDP requests to a custom callback.

Modules:
        conversions  Useful unit conversions for in-code use.
        mutable_val  Generic container for an immutable object that may change.
"""

import json
import logging
import socket
import sys
from collections import Iterator, Iterable
from datetime import datetime
from os.path import join, dirname

import socketserver

from pyliner.util.stream_logger import StreamLogger


class OverlayDict(object):
    """Limited dict implementation that allows for fallback on key lookup."""
    def __init__(self, *layers):
        self.layers = list(layers)

    def __getitem__(self, item):
        for layer in self.layers:
            if item in layer:
                return layer[item]
        raise KeyError(item)


class ThreadedUDPRequestHandler(socketserver.BaseRequestHandler):
    def __init__(self, callback, *args, **keys):
        self.callback = callback
        socketserver.BaseRequestHandler.__init__(self, *args, **keys)

    def handle(self):
        self.callback(self.request)


def enable_logging(log_dir=None, log_file=None, script=None, level=logging.INFO,
                   filemode='a', stdin=logging.INFO, stdout=logging.INFO,
                   stderr=logging.ERROR):
    """Enable the base logger, which all other logging bases off of.

    Logs stdin, stdout, and stderr if a logging level is passed to them.

    Args:
        log_dir (str): If None, defaults to '<pyliner>/logs'.
        log_file (str): If None, defaults to '<time>_pyliner_<script_name>.log'.
        script (str): Script name, only used if log_file is None.
        level: The level to log at.
        filemode: The filemode of the log file. Either 'a' or 'w'.
        stdin: Logging level or None
        stdout: Logging level or None
        stderr: Logging level or None
    """
    if log_dir is None:
        log_dir = join(dirname(__file__), 'logs')
    if log_file is None:
        now = datetime.now()
        time_str = now.strftime('%Y-%m-%d_%H:%M:%S')
        log_file = '{}_pyliner_{}.log'.format(time_str, script)

    log_path = join(log_dir, log_file)
    print('Log at {}'.format(log_path))
    logging.basicConfig(
        level=level,
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        # datefmt='%Y-%m-%d_%H:%M:%S',
        filename=log_path,
        filemode=filemode
    )
    if stdin is not None:
        sys.stdin = StreamLogger('stdin', sys.stdin, stdin)
    if stdout is not None:
        sys.stdout = StreamLogger('stdout', sys.stdout, stdout)
    if stderr is not None:
        sys.stderr = StreamLogger('stderr', sys.stderr, stderr)


def get_time():
    return int(
        (datetime.utcnow() - datetime(1970, 1, 1)).total_seconds() * 10000)


def handler_factory(callback):
    """ Creates server object and sets the callback """
    return lambda *args, **kwargs: ThreadedUDPRequestHandler(callback, *args,
                                                             **kwargs)


def indent(level, iterable):
    """Indent every line in a string by `level` spaces."""
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
        if sys.version_info.major < 3:
            choice = raw_input().lower()
        else:
            choice = input().lower()
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
