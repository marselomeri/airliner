import logging


class StreamLogger(object):
    """Intercepts IO to a stream and logs it."""
    def __init__(self, name, stream, level=logging.INFO):
        self.level = level
        self.name = name
        self.stream = stream
        self.log = logging.getLogger(name)

    def flush(self):
        return self.stream.flush()

    def read(self, length):
        result = self.stream.read(length)
        self.log.log(self.level, '(read) %s', repr(result))
        return result

    def readline(self):
        result = self.stream.readline()
        self.log.log(self.level, '(readline) %s', repr(result))
        return result

    def write(self, s):
        if not s.isspace():
            self.log.log(self.level, '(write) %s', repr(s))
        self.stream.write(s)
