import pyliner

run_flag = True
cmd_count = 0
total_frames = 0
current_frame = -1
recv_frame = -1
sent_frame = 0

def cmd_count_callback(data):
    global cmd_count
    cmd_count = data['params']['CmdCounter']['value']
    #print "Cmd counter: " + str(cmd_count)

airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json", "test_name": "demo_challenge"})
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'CmdCounter'}]}, cmd_count_callback)                         

while run_flag:
    total_frames += 1
    #current_frame = get frame num()
    
    if current_frame % 200 == 0:
        airliner.send_command({'name':'/Airliner/ES/Noop'})
        sent_frame = total_frames
    
    if recv_frame != -1:
        run_flag = False
        
    # Something to make this loop wait till next frame

print "Cmd processed in %s frames" % (recv_frame - sent_frame)

