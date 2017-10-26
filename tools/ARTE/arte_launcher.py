"""

   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.
 3. Neither the name Windhover Labs nor the names of its 
    contributors may be used to endorse or promote products derived 
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

"""
import shlex, subprocess
from datetime import datetime

class ArteSubprocess(object):
    """A subprocess of ARTE. Subprocesses have the following properties:

    Args:
        command (str): A single string with program path and arguments.
        fileName (str): Filename to save stdout to.
        cwd (path): The path that the command should use as the current
            working directory.
        terminalBool (boolean, optional): Optionally pipe output to a
            terminal. Not implemented.

    Attributes:
        command: A single string with program path and arguments.
        fileName: Filename to save stdout to.
        args: The tokenized command string.
        lastStatus: Return code.
        proc: The subprocess object.
    """
    def __init__(self, command, fileName, cwd, terminalBool = False):
        self.command = command
        self.args = shlex.split(command)
        self.fileName = fileName
        self.cwd = cwd

        f = open(self.fileName, "a")
        f.write("- ARTE " + str(command) + " " + datetime.now().strftime('%Y%m%d_%H:%M:%S - ') + "\n")
        self.proc = subprocess.Popen(self.args,stdout=f, stderr=f, shell=False, cwd=self.cwd)
        if terminalBool:
            # TODO add terminal pipe option
            pass
        self.lastStatus = None
        
    def stop_subprocess(self):
        """ Mimics subprocess terminate which sends SIGTERM."""
        self.proc.terminate()
        
    def kill_subprocess(self):
        """ Mimics subprocess kill which sends SIGKILL."""
        self.proc.kill()
    
    def pend_subprocess(self):
        """ Mimics subprocess wait pending forever.
        
        Note:
             Sets the lastStatus attribute with the return code.

        Returns:
            int: The subprocess return code.
        """
        self.lastStatus = self.proc.wait()
        return self.lastStatus
        
    def poll_subprocess(self):
        """ Mimics subprocess poll.

        Note:
            Sets the lastStatus attribute with the return code.

        Returns:
            int: The subprocess return code.
        """
        self.lastStatus = self.proc.poll()
        return self.lastStatus

