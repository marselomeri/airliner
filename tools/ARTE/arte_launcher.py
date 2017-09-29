import shlex, subprocess
from datetime import datetime

class arte_subprocess(object):
    """A subprocess of ARTE. Subprocesses have the following properties:

    Args:
        command (str): A single string with program path and arguments.
        fileName (str): Filename to save stdout to.

    Attributes:
        command: A single string with program path and arguments.
        fileName: Filename to save stdout to.
        args: The tokenized command string.
        lastStatus: Return code.
        proc: The subprocess object.
    """
    def __init__(self, command, fileName):
        self.command = command
        self.args = shlex.split(command)
        self.fileName = fileName
        f = open(self.fileName, "a")
        f.write("- ARTE " + str(command) + " " + datetime.now().strftime('%Y%m%d_%H:%M:%S - ') + "\n")
        self.proc = subprocess.Popen(self.args,stdout=f, shell=False)
        self.lastStatus = None
        
    def stop_subprocess(self):
        self.proc.terminate()
    
    def pend_subprocess(self):
        self.lastStatus = self.proc.wait()
        return self.lastStatus
        
    def poll_subprocess(self):
        self.lastStatus = self.proc.poll()
        return self.lastStatus

