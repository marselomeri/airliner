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
from pyliner.apps import App, AppAccess
from pyliner.intent import Intent, IntentNoReceiverError
from pyliner.intent import IntentFilter
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
        self.is_shutdown = False
        self.vehicle_id = vehicle_id

        # self._dynamic_filters = set()
        self._intent_filters = defaultdict(lambda: set())
        """:type: dict[str, set[AppAccess]]"""

    def add_filter(self, intent_filter, app):
        # type: (IntentFilter, AppAccess) -> None
        """Add an intent filter to this vehicle.

        Args:
            intent_filter (IntentFilter): The filter to add.
            app (AppAccess): If an intent matches a filter, the app to call.
        """
        for action in intent_filter.actions or []:
            self._intent_filters[action].add(app)

    def attach_app(self, app):
        """Attach an app to this vehicle.

        Args:
            app (App): The app to attach to this vehicle.
        """
        if app.qualified_name in self.apps:
            raise ValueError('Attempting to enable an App with the same name as'
                             ' an existing app.')
        elif not isinstance(app, App):
            return TypeError('app must be a subclass of App.')

        vehicle_token = AppAccess(app)
        self.apps[app.qualified_name] = vehicle_token
        vehicle_token.attach(self)

    def broadcast(self, intent):
        # type: (Intent) -> IntentFuture
        """Broadcast an Intent to listening Apps."""
        future = IntentFuture(caused_by=intent)
        # TODO Multithreading is a headache
        # threading.Thread(target=self._broadcast_thread, args=(intent, future))\
        #     .start()
        self._broadcast_thread(intent, future)
        return future

    def _broadcast_thread(self, intent, future):
        # type: (Intent, IntentFuture) -> None
        """Called by broadcast. Broadcasts intents to listening Apps.

        May be in a separate thread.
        """
        self.debug('Broadcasting: ' + str(intent))
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
        future.complete = True

    def detach_app(self, name):
        """Disable an app by removing it from this vehicle.

        Note:
            Any apps that attempt to call the disabled app by name will
            raise a KeyError.
        """
        try:
            app = self.apps[name]
        except KeyError:
            raise KeyError('Cannot find App to detach.')
        del self.apps[name]
        app.detach()

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
