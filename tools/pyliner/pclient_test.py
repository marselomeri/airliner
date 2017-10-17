from pyliner_client import PylinerClient

pc = PylinerClient({'test_name': 'frame_analyzer'})
pc.minmax_frame_analysis({'name':'/Airliner/ES/Noop'}, {'tlm': ['/Airliner/ES/HK/CmdCounter']})

pc.arte_client.send_shutdown()
pc.arte_client.close_conn()
