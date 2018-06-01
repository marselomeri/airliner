import logging
from logging import FileHandler

from service import Service


class LoggingService(Service):
    TAG = 'LoggingService'

    def __init__(self, log_name, log_file=None):
        super(LoggingService, self).__init__()
        self.log = logging.getLogger(log_name)

        file_handler = FileHandler(log_file)
        self.log.addHandler(file_handler)

    def _log(self, event):
        self.log.handle(event)

    def start(self):
        super(LoggingService, self).start()

    def stop(self):
        super(LoggingService, self).stop()
