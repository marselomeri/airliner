from arte_client import ArteClient
from pyliner import Pyliner
import time

class PylinerClient(Pyliner):
    
    def __init__(self, **kwargs):
        super(PylinerClient, self).__init__()
        self.ip = kwargs.get("ip", "localhost")
        self.port = kwargs.get("port", 9999)
        self.minor_frames = kwargs.get("minor_frames", 200)
        self.current_frame = 0
        self.total_frames = 0
        self.arte_client = ArteClient(self.ip, self.port)
        self.step_frame()
   
    def step_frame(self, num = 1):
        """ Signal ARTE to step to next frame specified number of times """
        for i in range(num):
            self.arte_client.send_ready()
            self.arte_client.receive_response()
            self.current_frame = self.arte_client.sequence
            self.total_frames += 1
    
    def frame_analysis(self, op, tlm):
        """ Analyze frames required to receive telemetry for this command """
        wait_flag = True
        frame_callback_var = 0
        recv_frame = 0
        sent_frame = 0
        
        # TODO: Not hard code
        def frame_analyze_cb(data):
            global frame_callback_var
            frame_callback_var = data['params']['CmdCounter']['value']
            print "Cmd counter: " + str(cmd_count)
        
        self.subscribe(tlm, frame_analyze_cb)
        
        # TODO: Loop safegaurd
        while wait_flag:
            time.sleep(0.01)
            self.step_frame()
            
            if self.current_frame % self.minor_frames == 0:
                self.send_message(op)
                sent_frame = self.total_frames
            
            if frame_callback_var == 1:
                wait_flag = False
                recv_frame = self.total_frames
        
        self.subscribers.pop()
        return recv_frame - sent_frame
            



