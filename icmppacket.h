#ifndef ICMPPACKET_H
#define ICMPPACKET_H

#include <vector>
#include <string>

#include "commonpacket.h"

using namespace std;

class icmpPacket
{
public:
    icmpPacket();
    ~icmpPacket();
    unsigned char Type;
    unsigned char Code;
    unsigned char Checksum[2];
    unsigned int Identifier;
    unsigned int SequenceNumber;
    vector<unsigned char> Payload;
    unsigned char Interface;
    icmpPacket &operator= (const icmpPacket &obj);
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
