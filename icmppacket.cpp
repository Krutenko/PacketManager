#include "icmppacket.h"

icmpPacket::icmpPacket()
{
    Type = 0;
    Code = 0;
    Checksum[0] = 0;
    Checksum[1] = 0;
    Identifier = 0;
    SequenceNumber = 0;
}

icmpPacket &icmpPacket::operator=(const icmpPacket &obj)
{
    int i;
    Type = obj.Type;
    Code = obj.Code;
    Checksum[0] = obj.Checksum[0];
    Checksum[1] = obj.Checksum[1];
    Identifier = obj.Identifier;
    SequenceNumber = obj.SequenceNumber;
    Payload = obj.Payload;
    return *this;
}

void icmpPacket::convertToSend()
{
    int i;
    size = 8 + Payload.size();
    packetSend = (unsigned char *) malloc(size * sizeof(unsigned char));
    packetSend[0] = Type;
    packetSend[1] = Code;
    packetSend[6] = Checksum[0];
    packetSend[7] = Checksum[1];
    packetSend[2] = Identifier / 256;
    packetSend[3] = Identifier % 256;
    packetSend[4] = SequenceNumber / 256;
    packetSend[5] = SequenceNumber % 256;
    for (i = 0; i < Payload.size(); i++)
        packetSend[8 + i] = Payload[i];
}

void icmpPacket::convertToFile()
{
    int i;
    packetFile = "";
    packetFile += CommonPacket::CharToHex((char) ICMP_CODE);
    convertToSend();
    for (i = 0; i < size; i++)
    {
        packetFile.push_back(CommonPacket::CharToHex(packetSend[i] / 16));
        packetFile.push_back(CommonPacket::CharToHex(packetSend[i] % 16));
    }
}

string icmpPacket::convertToRaw()
{
    int i;
    string packetRaw;
    packetRaw = "";
    convertToSend();
    for (i = 0; i < size; i++)
    {
        packetRaw.push_back(CommonPacket::CharToHex(packetSend[i] / 16));
        packetRaw.push_back(CommonPacket::CharToHex(packetSend[i] % 16));
    }
    return packetRaw;
}

void icmpPacket::convertFromSend()
{
    int i;
    Type = packetSend[0];
    Code = packetSend[1];
    Checksum[0] = packetSend[2];
    Checksum[1] = packetSend[3];
    Identifier = packetSend[4] * 256 + packetSend[5];
    SequenceNumber = packetSend[6] * 256 + packetSend[7];
    for (i = 8; i < size; i++)
        Payload.push_back(packetSend[i]);
}

void icmpPacket::convertFromFile()
{
    int i, k;
    packetSend = (unsigned char *) malloc(((packetFile.size() / 2 ) - 1) * sizeof(unsigned char));
    k = 0;
    for (i = 1; i < packetFile.size(); i += 2)
    {
        packetSend[k] = CommonPacket::HexToChar(packetFile[i], packetFile[i + 1]);
        k++;
    }
    size = packetFile.size() / 2;
    convertFromSend();
}

icmpPacket::~icmpPacket()
{

}
