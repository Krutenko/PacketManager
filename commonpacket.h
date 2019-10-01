#ifndef COMMONPACKET_H
#define COMMONPACKET_H

#include "packetsender.h"

#define IP_CODE 1
#define TCP_CODE 2
#define UDP_CODE 3
#define ICMP_CODE 4
#define IPTOSBUFFERS 12

class CommonPacket
{
public:
    CommonPacket();
    static unsigned char HexToChar(unsigned char h, unsigned char l);
    static unsigned char CharToHex(unsigned char c);
    static char *iptos(unsigned long in);
};

#endif
