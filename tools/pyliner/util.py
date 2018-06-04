import json
import logging
import socket
import sys
import threading
import time
from collections import Iterator, Iterable
from datetime import datetime
from os.path import join, dirname

import socketserver
from flufl.enum import Enum


class EventType(Enum):
    CONSOLE_OUT = 'CONSOLE_OUT'
    CONSOLE_IN = 'CONSOLE_IN'
    LOG = 'LOG'


class Event(object):
    def __init__(self, type):
        self.type = type


class LogStream(object):
    def __init__(self, name, stream, level=logging.INFO):
        self.level = level
        self.name = name
        self.stream = stream

    def read(self, length):
        result = self.stream.read(length)
        logging.log(self.level, '%s (read) - %s', self.name, repr(result))
        return result

    def readline(self):
        result = self.stream.readline()
        logging.log(self.level, '%s (readline) - %s', self.name, repr(result))
        return result

    def write(self, s):
        if not s.isspace():
            logging.log(self.level, '%s (write) - %s', self.name, repr(s))
        self.stream.write(s)


class PeriodicExecutor(threading.Thread):
    """Executes a callback function every x-seconds.

    Optionally takes callbacks for exception and last-pass handling.
    """

    def __init__(self, callback, every=1, exception=None, finalize=None,
                 name=None):
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
        super(PeriodicExecutor, self).__init__(name)
        self.daemon = True

        self.callback = callback
        # TODO if move to Python 3, use lambda x: print(x) if exception is None
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
                logging.exception('Exception in thread %s', self.name)
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


class ScriptingWrapper:
    def __init__(self, vehicle, failure_callback=None):
        """Wraps a vehicle for a scripting environment.

        Implements context manager (with-statement) functionality. Unhandled
        exceptions in the context manager are passed to `failure_callback` to
        give the user a chance to fail gracefully before exiting the context
        manager.

        Apps on the vehicle are accessible by their name (pyliner.app).

        Args:
            vehicle (BasePyliner): The vehicle to wrap.
            failure_callback (Callable[[Pyliner, Tuple], None]): Function
                handle that will be invoked on an unhandled exception of the
                controlling script.
        """
        self._vehicle = vehicle
        self.geographic = vehicle.geographic
        self.failure_callback = failure_callback

    def __getattr__(self, item):
        apps = self._vehicle.apps
        if item in apps:
            return apps[item]
        raise AttributeError('{} is not a method or module of this '
                             'Pyliner instance.'.format(item))

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        # If the context manager exits without error, all good. Otherwise...
        if exc_type:
            if callable(self.failure_callback):
                self.failure_callback(self, (exc_type, exc_val, exc_tb))
            else:
                print('Error in execution. Returning to Launch')
                self._vehicle.apps['ctrl'].rtl()


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
    if stdin:
        sys.stdin = LogStream('stdin', sys.stdin, stdin)
    if stdout:
        sys.stdout = LogStream('stdout', sys.stdout, stdout)
    if stderr:
        sys.stderr = LogStream('stderr', sys.stderr, stderr)


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
