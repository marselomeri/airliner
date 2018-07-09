"""
The Base Vehicle module exposes the base class for Vehicle. A lot of the setup
for intra-vehicle communication occurs here.

Classes:
    BaseVehicle  The base class for Vehicle
"""
import atexit
import logging
import threading
from abc import ABCMeta
from collections import defaultdict
from datetime import datetime
from os.path import join

from junit_xml import TestCase, TestSuite

from pyliner.action import ACTION_VEHICLE_SHUTDOWN
from pyliner.app import App, AppAccess
from pyliner.intent import Intent, IntentNoReceiverError
from pyliner.intent import IntentFuture
from pyliner.util.loggable import Loggable


class BaseVehicle(Loggable):
    """
    Contains the bare-minimum required for Pyliner. All additional functionality
    is provided through the Vehicle class. App management is performed via the
    app-lifecycle methods.
    """
    __metaclass__ = ABCMeta

    def __init__(self, vehicle_id, logger=None):
        """Constructor for BaseVehicle.

        Args:
            vehicle_id: Vehicle ID. Should be unique.
        """
        super(BaseVehicle, self).__init__(
            logger or logging.getLogger(vehicle_id))

        # Register Shutdown
        atexit.register(self.shutdown)

        # Instance attributes
        # self.broadcast_pool = ThreadPool # TODO Python 3
        self.apps = {}
        """:type: dict[str, AppAccess]"""
        self._intent_filters = defaultdict(lambda: set())
        """:type: dict[str, set[AppAccess]]"""
        self.is_shutdown = False
        self.vehicle_id = vehicle_id

    def add_filter(self, intent_filter, app):
        """Add an intent filter to this vehicle.

        Args:
            intent_filter (IntentFilter): The filter to add.
            app (AppAccess): If an intent matches a filter, the app to call.
        """
        for action in intent_filter.actions:
            self._intent_filters[action].add(app)

    def attach_app(self, app):
        """Attach an app to this vehicle.

        Args:
            app (App): The app to attach to this vehicle.
        """
        if app.qualified_name in self.apps:
            raise ValueError('Attempting to enable a module on top of an '
                             'existing module.')
        elif not isinstance(app, App):
            return TypeError('module must implement App.')

        vehicle_token = AppAccess(app)
        self.apps[app.qualified_name] = vehicle_token
        vehicle_token.attach(self)

    def broadcast(self, intent):
        # type: (Intent) -> IntentFuture
        """Broadcast an Intent to components."""
        self.debug('Broadcasting: {}'.format(intent))
        future = IntentFuture(caused_by=intent)
        # TODO Multithreading is a headache
        # threading.Thread(target=self._broadcast_thread, args=(intent, future))\
        #     .start()
        self._broadcast_thread(intent, future)
        future.complete = True  # If multi-thread, move this somewhere else.
        return future

    def _broadcast_thread(self, intent, future):
        # type: (Intent, IntentFuture) -> None
        if intent.is_explicit():
            self.apps[intent.component].receive(intent, future)
        else:
            try:
                intent_filters = self._intent_filters[intent.action]
            except KeyError:
                future.failure = IntentNoReceiverError(
                    'There are no Apps accepting {}.'.format(intent.action))
            else:
                for app in intent_filters:
                    app.receive(intent, future)

    def detach_app(self, name):
        """Disable an app by removing it from this vehicle.

        Note:
            Any apps that attempt to call the disabled app by name will
            produce an error.
        """
        if name not in self.apps:
            raise AttributeError(
                'Cannot disable a module that was never enabled.')
        module = self.apps[name]
        del self.apps[name]
        module.detach()

    def remove_filter(self, intent_filter, app):
        """Remove an intent filter from this vehicle."""
        for action in intent_filter.actions:
            self._intent_filters[action].remove(app)

    def shutdown(self):
        """Shutdown all components on vehicle and detach.

        This method is normally registered to be called automatically at
        interpreter exit.

        Shutdown Order:
            1. Stop Apps
            2. Stop Services
            3. Detach Apps
            4. Detach Services
            5. Detach Sensors
        """
        self.info('Vehicle {} is shutting down.'.format(self.vehicle_id))
        if not self.is_shutdown:
            self.is_shutdown = True
            self.broadcast(Intent(action=ACTION_VEHICLE_SHUTDOWN))
            for app in self.apps.values():
                app.detach()
        self.info('Shutdown complete.')

    # Testing Code. TODO Figure out where to put this
    def assert_equals(self, a, b, description):
        """ Assert for Pyliner that tracks passes and failures """
        if a == b:
            self.passes += 1
            self.test_description.append(description)
            self.log('Valid assertion made: %s == %s' % (a, b))
        else:
            self.fails += 1
            self.test_description.append(description)
            self.log('Invalid assertion made: %s == %s' % (a, b), LogLevel.Warn)

    def assert_not_equals(self, a, b, description):
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
