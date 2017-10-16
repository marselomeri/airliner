from arte_client import ArteClient
import logging
from pyliner import Pyliner
import time

class PylinerClient(Pyliner):

    def __init__(self, kwargs):
        super(PylinerClient, self).__init__(**kwargs)
        self.ip = kwargs.get("ip", "localhost")
        self.port = kwargs.get("port", 9999)
        self.minor_frames = kwargs.get("minor_frames", 200)
        self.current_frame = 0
        self.total_frames = 0
        self.arte_client = ArteClient(self.ip, self.port)
   
    def step_frame(self, num = 1):
        """ Signal ARTE to step to next frame specified number of times """
        for i in range(num):
            self.arte_client.send_ready()
            self.arte_client.receive_response()
            self.current_frame = self.arte_client.sequence
            self.total_frames += 1
            
    def step_until(self, cb):
        """ Signal ARTE to step until the specified callback returns true """
        while not cb():
            self.step_frame()
            
    
    def frame_analysis(self, op, tlm, start_frame = 0):
        """ Analyze frames required to receive telemetry for this command """
        logging.info('Starting frame analysis')
        wait_flag = True
        frame_callback_var = 0
        recv_frame = 0
        sent_frame = 0
        
        # TODO: Not hard code
        def frame_analyze_cb(data):
            global frame_callback_var
            frame_callback_var = data['params']['CmdCounter']['value']
            logging.info('Callback received value of: %s' % (frame_callback_var))
        
        # TODO: Not hard code this either
        self.send_command({'name':'/Airliner/ES/Reset'})
        self.subscribe(tlm, frame_analyze_cb)
        
        # TODO: Loop safegaurd
        while wait_flag:
            logging.info('Current frame: %s Total frames: %s' % (self.current_frame, self.total_frames))
            if self.current_frame > start_frame:
                time.sleep(0.01)
                
                if self.current_frame % self.minor_frames == 0:
                    self.send_command(op)
                    sent_frame = self.total_frames
                
                if frame_callback_var == 1:
                    wait_flag = False
                    recv_frame = self.total_frames
                    
            self.step_frame()
        
        self.subscribers.pop()
        result = recv_frame - sent_frame
        logging.info('Frame analysis for %s: %s' % (op, result))
        return result
        
    def minmax_frame_analysis(self, op, tlm):
        """ Analyze frames required to receive telemetry for this command """
        logging.info('Starting min max frame analysis')
        
        best_frame_time = self.minor_frames

        for start_frame in range(1, self.minor_frames):
            frame_time = self.frame_analysis(op, tlm)
            if frame_time < best_frame_time:
                best_frame_time = frame_time

        logging.info('Min max frame analysis for %s: min:%s max:%s' % (best_frame_time, self.minor_frames -1))
        return result
            



