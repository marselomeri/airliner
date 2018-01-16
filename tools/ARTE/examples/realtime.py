import time
from arte_client import ArteClient

IP, PORT = "localhost", 9999
client = ArteClient(IP, PORT)
client.send_ready()
client.receive_response()
time.sleep(20)
client.send_shutdown(True)
client.close_conn()
