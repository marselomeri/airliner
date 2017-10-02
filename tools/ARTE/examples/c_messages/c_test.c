#include <stdio.h>
#include <unistd.h> // for close
#include "nanopb/pb_encode.h"
#include "nanopb/pb_decode.h"
#include "ccsds.h"
#include "msg.pb.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


//void CCSDS_InitPkt (CCSDS_PriHdr_t  *PktPtr,
                    //uint16           StreamId,
                    //uint16           Length,
                    //boolean          Clear )
//{
   //uint16     SeqCount;

   ///* Save the sequence count in case it must be preserved. */
   //SeqCount = CCSDS_RD_SEQ(*PktPtr);

   ///* Zero the entire packet if needed. */
   //if (Clear)  CFE_PSP_MemSet((void *)PktPtr, 0, Length);

   ///* Clear the primary header. */
   //CCSDS_CLR_PRI_HDR(*PktPtr);

   ///* Set the stream ID and length fields in the primary header. */
   //CCSDS_WR_SID(*PktPtr, StreamId);
   //CCSDS_WR_LEN(*PktPtr, Length);

   ///* Restore the sequence count if needed. */
   //if (!Clear)  CCSDS_WR_SEQ(*PktPtr, SeqCount);

//} 


int main()
{
    uint16 Length = 10;
    CCSDS_TlmPkt_t command_packet;
    test_msg_int test_proto_msg = test_msg_int_init_zero;
    size_t message_length;
    bool status;
    uint8_t buffer[128];
    
    /* Create a stream that will write to our buffer. */
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    
    /* Fill in a random number */
    test_proto_msg.content = 13;
    
    /* Now we are ready to encode the message! */
    status = pb_encode(&stream, test_msg_int_fields, &test_proto_msg);
    message_length = stream.bytes_written;
    
    /* Then just check for any errors.. */
    if (!status)
    {
        printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        return 1;
    }
    
    // Plus seven because CCSDS_WR_LEN subtracts the secondary header 
    // (six) and the one per the packet spec 
    CCSDS_WR_LEN(command_packet.PriHdr, message_length + 3);
    
    printf("Command packet total length = %u\n", CCSDS_RD_LEN(command_packet.PriHdr));
    printf("Protobuf message length = %lu\n", message_length);
    
    // Send the command packet and payload
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    /* Connect to server running on localhost:9999 */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    servaddr.sin_port = htons(9999);
    
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        perror("connect");
        return 1;
    }
    send(sockfd, &command_packet, sizeof(command_packet), 0);
    //send(sockfd, &stream, message_length, 0);
    
    close(sockfd);

    return 0;
}
