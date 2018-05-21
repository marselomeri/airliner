import logging
from abc import abstractmethod, ABCMeta
from builtins import isinstance
from datetime import datetime
from genericpath import exists
from os import mkdir
from os.path import join, dirname, realpath

from junit_xml import TestCase, TestSuite

from pyliner_module import PylinerModule
from util import LogLevel


class BasePyliner(object):
    __metaclass__ = ABCMeta

    def __init__(self, script_name=None, log_dir=None):
        if log_dir is None:
            log_dir = join(dirname(realpath(__file__)), "logs")

        self._modules = {}
        """:type: Dict[str, PylinerModule]"""
        self.start_time = datetime.now()

        # Logging
        self.fails = 0
        self.script_name = script_name
        self.log_name = self.start_time.strftime("%Y-%m-%d_%I:%M:%S") + \
                        "_pyliner_" + self.script_name + ".log"
        self.test_description = []
        self.passes = 0
        self.log_dir = log_dir
        self.duration = 0
        self._setup_log()

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        # If the context manager exits without error, all good. Otherwise...
        if exc_type:
            self.critical_failure(exc_type, exc_val, exc_tb)

    def __getattr__(self, item):
        if item in self._modules:
            return self._modules[item]
        raise AttributeError('{} is not a function or module of this '
                             'Pyliner instance.'.format(item))

    @abstractmethod
    def critical_failure(self, exc_type, exc_val, exc_tb):
        raise NotImplementedError()

    def disable_module(self, name):
        """Disable a module by removing it from the vehicle.

        Note:
            Any modules that attempt to call the disabled module will produce
            an error.
        """
        if name in self._modules:
            raise AttributeError('Cannot disable a module that was never '
                                 'enabled.')
        self._modules[name].detach()
        del self._modules[name]

    def enable_module(self, name, module):
        """Enable a Pyliner Module on this vehicle."""
        if name in self._modules:
            raise ValueError('Attempting to enable a module on top of an '
                             'existing module.')
        if not isinstance(module, PylinerModule):
            return TypeError('module must implement PylinerModule.')
        module.attach(self)
        self._modules[name] = module

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

    @property
    def modules(self):
        return self._modules.copy()

    def _setup_log(self):
        """ Setup log for Pyliner """
        if not exists(self.log_dir):
            mkdir(self.log_dir)

        logging.basicConfig(format='%(asctime)s\t%(levelname)s: %(message)s',
                            datefmt='%m/%d/%Y %I:%M:%S %p',
                            filename=join(self.log_dir, self.log_name),
                            level=logging.DEBUG)

    # Testing Code. TODO Figure out where to put this
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
        with open(join(self.log_dir, self.log_name[:-3]) + 'tlm',
                  'w') as tlm_file:
            for tlm in self.all_telemetry:
                tlm_file.write(str(tlm) + '\n')

    def get_test_results(self):
        """ Generates a string with all test results """
        time_diff = datetime.now() - self.start_time
        diff = divmod(time_diff.total_seconds(), 60)
        duration = "%i minutes %i seconds" % (diff[0], diff[1]) if diff[0] > 0 \
            else "%i seconds" % (diff[1])
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
        self.dump_tlm()
        print(self.get_test_results())
        self.generate_junit()

    def generate_junit(self):
        # Get the test count
        test_count = self.passes + self.fails
        # Add the first test case
        test_cases = [
            TestCase(self.script_name + str(0), '', self.duration / test_count,
                     '', '')]
        # Add the remaining test cases
        for x in range(1, test_count):
            test_cases.append(TestCase(self.script_name + str(x), '',
                                       self.duration / test_count, '', ''))
        # Add any failure info
        for x in range(0, self.fails):
            test_cases[0].add_failure_info(self.test_description[x])
        ts = TestSuite("test suite", test_cases)
        with open(join(self.log_dir, self.script_name + '_results.xml'),
                  'w') as f:
            TestSuite.to_file(f, [ts], prettyprint=False)

    def reset_test(self):
        """ Reset  """
        pass  # Need this?
