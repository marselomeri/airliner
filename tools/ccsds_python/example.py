from ccsds_packets import *

if __name__ == '__main__':
    # instantiate a command packet
    command_packet = CCSDS_CmdPkt_t()
    # clear packet (0s)
    command_packet.clear_packet()
    
    # instantiate a telemetry packet
    telemetry_packet = CCSDS_TlmPkt_t()
    # clear packet (0s)
    telemetry_packet.clear_packet()
    
    # initialize the command packet
    command_packet.init_packet()
    
    # initialize the telemetry packet
    telemetry_packet.init_packet()
    
    # set the current time in the telemetry packet
    telemetry_packet.set_current_time()
    
    # print the size in bytes of the telemetry packet
    print("telemetry packet size bytes = ", telemetry_packet.get_packet_size())
    
    # print the telemetry packet time
    print("telemetry packet time = ", telemetry_packet.get_time())
    
    # print the telemetry packet type code from the primary header
    print("telemetry packet type code = ", telemetry_packet.PriHdr.StreamId.bits.type)

    # print the size in bytes of the command packet
    print("command packet size bytes = ", command_packet.get_packet_size())
    
    # print the command packet type code from the primary header
    print("command packet type code = ", command_packet.PriHdr.StreamId.bits.type)

    # encode a header packet
    encoded = command_packet.get_encoded()
    
    # instantiate a new command packet
    new_command_packet = CCSDS_CmdPkt_t()
    new_command_packet.clear_packet()
    
    # decode a header packet
    new_command_packet.set_decoded(encoded)
    
    # print encoded header
    print("encoded header = ", encoded)
    
    # print decoded header
    print("new header from encoded header = ", new_command_packet.get_encoded())
    
    # load a packet from hex
    ea_noop = bytes.fromhex("1c29c02300010000")
    
    # set the command packet equal to ea_noop
    command_packet.set_decoded(ea_noop)
    
    # print in hexidecimal
    command_packet.print_base16()
    
    # print in decimal
    command_packet.print_base10()
    
    #print in binary
    command_packet.print_base2()
    
    # clear the packet
    command_packet.clear_packet()
    
    # set the user data length. This automatically sets the length of 
    # the command_packet
    command_packet.set_user_data_length(7)
    
    #command_packet.init_packet()
    
    print("command packet user data size = ",command_packet.get_user_data_length())
    
    # set the user data length. This automatically sets the length of 
    # the command_packet. 
    command_packet.set_user_data_length(0)
    
    #print("command packet user data size = ", command_packet.get_user_data_length())
    
    # calculate the checksum for a command packet
    command_packet.set_checksum(0)
    
    #print("command packet checksum value = ", command_packet.SecHdr.Command.bits.checksum)
    
    # validate the checksum
    print("command packet validation = ", command_packet.validate_checksum(0))
    
    command_packet.clear_packet()
    
    # create a payload for a checksum check
    payload = bytes(b'\x01')

    command_packet.set_user_data_length(len(payload))
    
    command_packet.set_checksum(payload)
    
    print("command packet checksum value = ", command_packet.SecHdr.Command.bits.checksum)
    
    print("command packet validation = ", command_packet.validate_checksum(payload))

