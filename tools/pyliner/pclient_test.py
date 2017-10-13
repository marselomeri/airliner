from pyliner_client import PylinerClient

pc = PylinerClient({'test_name': 'frame_analyzer'})
pc.frame_analysis({'name':'/Airliner/ES/Noop'}, {'name': '/Airliner/ES/HK', 'args':[{'name':'CmdCounter'}]})
