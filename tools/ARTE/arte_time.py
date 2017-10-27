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
import time
from threading import Timer

class ArteWatchdog(object):
    """A watchdog timer for threads or any long running task.

    Note:
        ArteWatchdog implements threading.Timer. An instance of
        ArteWatchdog will instantiate a threading.Timer in the
        constructor and a new threading.Timer every reset.

    Args:
        timeout (uint): The timeout in seconds.
        event_handler (:obj:`ArteEventHandler`): An instance of an
            ArteEventHandler object.

    Attributes:
        timeout (uint): The timeout in seconds.
        event_handler (:obj:`ArteEventHandler`):  An instance of an
            ArteEventHandler object.
        timer (:obj:`threading.Timer`): The current threading.Timer 
            object.
    """
    def __init__(self, timeout, event_handler):
        self.timeout = timeout
        self.event_handler = event_handler
        self.timer = Timer(self.timeout, self.timeoutHandler)

    def start(self):
        """Starts the watchdog timer."""
        self.timer.start()

    def reset(self):
        """Resets the watchdog timer."""
        self.timer.cancel()
        #self.timer.join()
        self.timer = Timer(self.timeout, self.timeoutHandler)
        self.timer.start()

    def stop(self):
        """Stops the watchdog timer."""
        self.timer.cancel()
        self.timer.join()
    
    def timeoutHandler(self):
        """The handler called when watchdog timer expires. Triggers 
            the expired_watchdog event.
        """
        self.event_handler.expired_watchdog()


# TODO delete me not currently used
#class ArteTimeSource(object):
    #"""
    #Args:
        #seconds_increment (int): 
        #subseconds_increment (float):
    
    #"""
    #def __init__(self, seconds_increment, subseconds_increment):
        #self.start_time = 0
        #self.float_time = 0
        #self.seconds = 0
        #self.subseconds = 0
        #self.seconds_increment = seconds_increment
        #self.subseconds_increment = subseconds_increment
    
    #def convert_subseconds(self, fraction_time):
        #converted_time = 0
        #for n in range(16):
            #if (fraction_time/(2**-(n+1))) >= 1:
                #converted_time |= 1 << (16 - (n+1)) 
                #fraction_time -= 2**-(n+1)
        #return converted_time

    #def set_start_time(self):
        #self.start_time = self.float_time = time.time()
        #int_time = int(self.float_time)
        #fraction_time = self.float_time - int_time
        #self.seconds = int_time
        #self.subseconds = self.convert_subseconds(fraction_time)
        
    #def add_step_time(self):
        ## add a step increment to the time in floating point format.
        #self.float_time += (self.seconds_increment + self.subseconds_increment)
        ## add a step increment to the time in seconds.
        #self.seconds = int(self.float_time)
        ## add a step increment to the time in subseconds.
        #self.subseconds = self.convert_subseconds(self.float_time - int(self.float_time))
    
    #def get_time(self):
        #return self.seconds, self.subseconds
        
    #def print_time(self):
        #print("seconds ", self.seconds)
        #print("subseconds ", bin(self.subseconds))
        

