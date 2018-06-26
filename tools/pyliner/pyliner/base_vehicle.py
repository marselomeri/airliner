"""
The Base Vehicle module exposes the base class for Vehicle. A lot of the setup
for intra-vehicle communication occurs here.

Classes:
    BaseVehicle  The base class for Vehicle
"""
import atexit
import logging
import re
import threading
from abc import ABCMeta
from datetime import datetime
from os.path import join
from time import sleep

from junit_xml import TestCase, TestSuite
from sortedcontainers import SortedDict

from app import App, AppAccess
from communication import Communication
from pyliner.intent import IntentResponse
from pyliner.pyliner_exceptions import PylinerError
from pyliner.sensor import SensorAccess
from pyliner.sensor.geographic_sensor import GeographicSensor
from pyliner.sensor.time_sensor import TimeSensor
from pyliner.service import ServiceAccess
from pyliner.util.loggable import Loggable


class BaseVehicle(Loggable):
    """
    Contains the bare-minimum required for Pyliner. All additional functionality
    is provided through the Pyliner class. App management is performed via the
    app-lifecycle methods.

    By way of the communications instance given in the constructor, telemetry
    from the vehicle is exposed via the TODO methods.
    """
    __metaclass__ = ABCMeta

    def __init__(self, vehicle_id, communications, geographic=None,
                 logger=None, time=None):
        """Constructor for BasePyliner.

        Args:
            vehicle_id: Vehicle ID. Should be unique.
            communications (Communication): Communications PylinerModule.
                Not exposed as a public module for direct access, but the user
                is given the option to use a custom class if they desire.
            geographic: If None, defaults to Geographic().
            logger: If None, defaults to 'logging.getLogger(vehicle_id)'.
            time: If None, default to TimeSensor().
        """
        super(BaseVehicle, self).__init__(
            logger or logging.getLogger(vehicle_id))

        # Register Shutdown
        atexit.register(self.shutdown)

        # Instance attributes
        self.components = {'app': {}, 'service': {}, 'sensor': {}}
        """:type: dict[str, dict[str, SensorAccess]]"""
        self.com_priority = SortedDict()  # TODO Remove
        self.is_shutdown = False
        self.vehicle_id = vehicle_id

        # Pick passed sensors or Default
        geographic = geographic or GeographicSensor()
        time = time or TimeSensor()

        # Default components
        self.communications = communications
        self.attach_sensor('geographic', geographic)
        # self.attach_service('time', time)
        self.attach_service('comms', communications)

    def attach_app(self, priority, app_name, app):
        """Attach an app to this vehicle."""
        identifier = re.compile(r"^[^\d\W]\w*\Z")

        if priority in self.com_priority:
            raise ValueError('There is already a module with priority '
                             '{}'.format(priority))
        elif app_name in self.components['app']:
            raise ValueError('Attempting to enable a module on top of an '
                             'existing module.')
        elif not re.match(identifier, app_name):
            raise ValueError('Attempting to enable a module with an illegal '
                             'name. Module names must be valid Python '
                             'identifiers.')
        elif not isinstance(app, App):
            return TypeError('module must implement App.')

        vehicle_token = AppAccess(app_name)
        self.components['app'][app_name] = vehicle_token
        vehicle_token.attach(self, app)
        self.com_priority[priority] = app

    def attach_service(self, service_name, service):
        """Attach a service to this vehicle.

        Args:
            service_name (str): Name to identify this service.
            service (Service): Service to attach.
        """
        vehicle_token = ServiceAccess(service_name)
        self.components['service'][service_name] = vehicle_token
        vehicle_token.attach(self, service)

    def attach_sensor(self, sensor_name, sensor):
        """Attach a sensor to this vehicle.

        Args:
            sensor_name (str): Name to identify this sensor.
            sensor (Sensor): Sensor to attach.
        """
        vehicle_token = SensorAccess(sensor_name)
        self.components['sensor'][sensor_name] = vehicle_token
        vehicle_token.attach(self, sensor)

    def await_change(self, tlm, poll=1.0, out=None):
        """Block until the telemetry value changes.

        Args:
            tlm (str): The telemetry to monitor.
            poll (float): Check every `poll` seconds.
            out (Callable): If not None, call this every loop.
        """
        old_val = self.tlm_value(tlm)
        while self.tlm_value(tlm) == old_val:
            if out is not None:
                out()
            sleep(poll)
        return self.tlm_value(tlm)

    def broadcast(self, intent):
        """Broadcast an Intent to components."""
        self.debug('Broadcasting: {}'.format(intent))
        print('Broadcasting: {}'.format(intent))
        response = IntentResponse(caused_by=intent)
        if intent.is_explicit():
            kind, ident = intent.component.split('.')
            callback = self.components[kind][ident].receive
            threading.Thread(target=callback, args=(intent, response)).start()
        else:
            raise PylinerError('Can\'t do implicit intents now')
        return response

    def detach_app(self, name):
        """Disable an app by removing it from the vehicle.

        Note:
            Any apps that attempt to call the disabled app by name will
            produce an error.
        """
        apps = self.components['app']
        if name not in apps:
            raise AttributeError(
                'Cannot disable a module that was never enabled.')
        module = apps[name]
        del apps[name]
        module.detach()
        for priority, pri_module in self.com_priority.items():
            if module is pri_module:
                self.com_priority.pop(priority)

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
        if not self.is_shutdown:
            for app in self.components['app'].values():
                app.stop()
            for service in self.components['service'].values():
                service.stop()
            for app in self.components['app'].values():
                app.detach()
            for service in self.components['service'].values():
                service.detach()
            for sensor in self.components['sensor'].values():
                sensor.detach()
            self.is_shutdown = True

    def start_app(self, app_name):
        """Start an App."""
        self.components['app'][app_name].start()

    def start_service(self, service_name):
        """Start a Service."""
        self.components['service'][service_name].start()

    def telemetry(self):
        """Return telemetry to send, or None."""
        # Iterate through every app in priority order to see if any have
        # telemetry to send.
        for app in self.com_priority.values():
            if app.telemetry_available:
                return app.telemetry
        return None

    def tlm(self, tlm):
        """ Get all data of specified telemetry item.

        Args:
            tlm (str): Operational name of requested telemetry.

        Returns:
            dict: Telemetry data.

        Raises:
            KeyError: If telemetry is not found.
        """
        # TODO Rename variable _telemetry
        return self.communications._telemetry[tlm]

    def tlm_value(self, tlm):
        """ Get current value of specified telemetry item.

        Args:
            tlm (str): Operational name of requested telemetry.

        Returns:
            Any: Current value of telemetry.

        Raises:
            KeyError: If telemetry is not found.
        """
        return self.tlm(tlm)['value']

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
