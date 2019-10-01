#ifndef UNIPACKET_H
#define UNIPACKET_H

#include "ippacket.h"
#include "tcppacket.h"
#include "udppacket.h"
#include "icmppacket.h"

class uniPacket
{
public:
    uniPacket();
    ~uniPacket();
    unsigned int protocol;
    string protocolName;
    ipPacket *ip;
    tcpPacket *tcp;
    udpPacket *udp;
    icmpPacket *icmp;
    uniPacket &operator= (const ipPacket &obj);
    uniPacket &operator= (const tcpPacket &obj);
    uniPacket &operator= (const udpPacket &obj);
    uniPacket &operator= (const icmpPacket &obj);
    uniPacket &operator= (const uniPacket &obj);
};

#endif
