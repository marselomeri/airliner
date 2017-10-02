import arte_ccsds

if __name__ == '__main__':
    
    # example 1
    command_packet = CCSDS_CmdPkt_t()
    telemetry_packet = CCSDS_TlmPkt_t()
    
    telemetry_packet.set_current_time()
    telemetry_packet.print_base2()
    
    command_packet.init_packet()
    
    command_packet.print_base16()

    # example 2
    #command_packet = CCSDS_CmdPkt_t()
    #ea_noop = bytes.fromhex("1c29c02300010000")
    #command_packet.set_decoded(ea_noop)
    #command_packet.print_base16()
