#ifndef TCPPACKET_H
#define TCPPACKET_H

#include <vector>
#include <string>

#include "commonpacket.h"

using namespace std;

class tcpPacket
{
public:
    tcpPacket();
    ~tcpPacket();
    unsigned int SourcePort;
    unsigned int DestinationPort;
    unsigned long SequenceNumber;
    unsigned long AcknowledgmentNumber;
    unsigned char DataOffset;
    unsigned char Reserved;
    unsigned char Flags;
    unsigned int Window;
    unsigned char Checksum[2];
    unsigned int UrgentPointer;
    vector<unsigned char> Options;
    vector<unsigned char> Payload;
    unsigned char Interface;
    bool boxes[2];
    tcpPacket &operator= (const tcpPacket &obj);
    unsigned char *packetSend;
    unsigned int size;
    string packetFile;
    void convertToSend();
    void convertToFile();
    string convertToRaw();
    void convertFromSend();
    void convertFromFile();

private:
    int ihlIndex;
};

#endif
