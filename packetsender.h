#ifndef PACKETSENDER_H
#define PACKETSENDER_H

#define WIN32_LEAN_AND_MEAN
#include "pcap.h"
#ifndef WIN32
    #include <sys/socket.h>
    #include <netinet/in.h>
#else
    #include <winsock.h>
#endif

#include "commonpacket.h"

class PacketSender
{
public:
    PacketSender();
    static void send(unsigned int protocol, unsigned char *packet, unsigned int size);
    static pcap_if_t *getInt();
};

#endif
