class Telemetry(object):
    def __init__(self, name=None, args=None):
        if name is None:
            name = '/Airliner/CNTL/ManualSetpoint'
        self.name = name
        self.args = args

    @property
    def has_args(self):
        return self.args is not None

    def to_json(self):
        json = {'name': self.name}
        if self.has_args:
            json['args'] = [{'name': name, 'value': value}
                            for name, value in self.args]
        return json
