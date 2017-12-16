from websocket import create_connection
import  toolkit as tk
import time
counter = 2
temp = {"tlm":[{"name":"/CFS/CS/LastOneShotChecksum","format":"0x%08x"}]}
temp = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(temp['tlm'])) + '}}'
temp = temp.replace("\'", "\"")
data = '[1,1,'+str(counter)+',' + str(temp) + ']'


temp2 = {"tlm":[{"name":"/CFS/CS/LastOneShotChecksum"}]}
temp2 = ' {"parameter":"unsubscribe", "data":{"list":' + str(tk.byteify(temp2['tlm'])) + '}}'
temp2 = temp2.replace("\'", "\"")
data2 = '[1,1,'+str(counter)+',' + str(temp2) + ']'


#data = '[1, 1, 1, {"events": "subscribe"}]'
ws = create_connection('ws://127.0.0.1:8090/softsim/_websocket')
"""
def func(ws,data,c):

    print data
    ws.send(data)
    while True:
        result = ws.recv()
        if result != '[1,2,'+str(c)+']':

            yield result

while True:
    counter = counter + 1
    data = '[1,1,' + str(counter) + ',' + str(temp) + ']'
    #print
    func(ws,data,counter).next()
    time.sleep(1)
"""
ws.send(data)
count =0
while True:
    #print '==============',data2
    count+=1
    result = ws.recv()
    print result
    if count==5:
        print 'unubscribing'
        ws.send(data2)
        result = ws.recv()
        if result=='[1,2,'+str(counter)+']':
            print result
            break
    #time.sleep(0.1)