#ifndef UDPPACKET_H
#define UDPPACKET_H

#include <vector>
#include <string>

#include "commonpacket.h"

using namespace std;

class udpPacket
{
public:
    udpPacket();
    ~udpPacket();
    unsigned int SourcePort;
    unsigned int DestinationPort;
    unsigned int Length;
    unsigned char Checksum[2];
    vector<unsigned char> Payload;
    unsigned char Interface;
    udpPacket &operator= (const udpPacket &obj);
    unsigned char *packetSend;
    unsigned int size;
    string packetFile;
    void convertToSend();
    void convertToFile();
    string convertToRaw();
    void convertFromSend();
    void convertFromFile();
};

#endif
