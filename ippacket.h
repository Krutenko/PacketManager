#ifndef IPPACKET_H
#define IPPACKET_H

#include <vector>
#include <string>

#include "commonpacket.h"

using namespace std;

class ipPacket
{
public:
    ipPacket();
    ~ipPacket();
    unsigned char Version;
    unsigned char IHL;
    unsigned char TypeOfService;
    unsigned int TotalLength;
    unsigned int Identification;
    unsigned char Flags;
    unsigned int FragmentOffset;
    unsigned char TimeToLive;
    unsigned char Protocol;
    unsigned char HeaderChecksum[2];
    unsigned char SourceAddress[4];
    unsigned char DestinationAddress[4];
    vector<unsigned char> Options;
    vector<unsigned char> Payload;
    unsigned char Interface;
    bool boxes[4];
    ipPacket &operator= (const ipPacket &obj);
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
