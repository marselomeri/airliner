#import pyliner
from arte_ccsds import *

#airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json"})

ret_msg = CCSDS_CmdPkt_t()
ret_msg.clear_packet()
ret_msg.init_packet()
ret_msg.PriHdr.StreamId.bits.app_id = 0x1806
ret_msg.SecHdr.Command.bits.code = 0
ret_msg.set_checksum(0)
ret_msg.print_base16()


