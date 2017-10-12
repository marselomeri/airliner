from pyliner_client import PylinerClient

pc = PylinerClient()
pc.frame_analysis({'name':'/Airliner/ES/Noop'}, {'name': '/Airliner/ES/HK', 'args':[{'name':'CmdCounter'}]})
