#include "unipacket.h"

uniPacket::uniPacket()
{

}

uniPacket &uniPacket::operator=(const ipPacket &obj)
{
    ip = new ipPacket();
    *ip = obj;
    protocol = IP_CODE;
    protocolName = "IP";
    return *this;
}

uniPacket &uniPacket::operator=(const tcpPacket &obj)
{
    tcp = new tcpPacket();
    *tcp = obj;
    protocol = TCP_CODE;
    protocolName = "TCP";
    return *this;
}

uniPacket &uniPacket::operator=(const udpPacket &obj)
{
    udp = new udpPacket();
    *udp = obj;
    protocol = UDP_CODE;
    protocolName = "UDP";
    return *this;
}

uniPacket &uniPacket::operator=(const icmpPacket &obj)
{
    icmp = new icmpPacket();
    *icmp = obj;
    protocol = ICMP_CODE;
    protocolName = "ICMP";
    return *this;
}

uniPacket &uniPacket::operator=(const uniPacket &obj)
{
    *ip = *obj.ip;
    *tcp = *obj.tcp;
    *udp = *obj.udp;
    *icmp = *obj.icmp;
    protocol = obj.protocol;
    protocolName = obj.protocolName;
    return *this;
}

uniPacket::~uniPacket()
{
    switch (protocol)
    {
    case IP_CODE:
    {
        delete ip;
        break;
    }
    case TCP_CODE:
    {
        delete tcp;
        break;
    }
    case UDP_CODE:
    {
        delete udp;
        break;
    }
    case ICMP_CODE:
    {
        delete icmp;
        break;
    }
    default:
        return;
    }
}
