#include "packetsender.h"

PacketSender::PacketSender()
{

}

void PacketSender::send(unsigned int protocol, unsigned char *packet, unsigned int size)
{
    //send
}

pcap_if_t *PacketSender::getInt()
{
    pcap_if_t *alldevs;
    int i = 0;
    char errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs_ex(strdup(PCAP_SRC_IF_STRING), NULL, &alldevs, errbuf) == -1)
        return NULL;
    return alldevs;
}
