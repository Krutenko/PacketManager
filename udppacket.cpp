#include "udppacket.h"

udpPacket::udpPacket()
{
    SourcePort = 0;
    DestinationPort = 0;
    Length = 0;
    Checksum[0] = 0;
    Checksum[1] = 0;
}

udpPacket &udpPacket::operator=(const udpPacket &obj)
{
    int i;
    SourcePort = obj.SourcePort;
    DestinationPort = obj.DestinationPort;
    Length = obj.Length;
    Checksum[0] = obj.Checksum[0];
    Checksum[1] = obj.Checksum[1];
    Payload = obj.Payload;
    return *this;
}

void udpPacket::convertToSend()
{
    int i;
    size = 8 + Payload.size();
    packetSend = (unsigned char *) malloc(size * sizeof(unsigned char));
    packetSend[0] = SourcePort / 256;
    packetSend[1] = SourcePort % 256;
    packetSend[2] = DestinationPort / 256;
    packetSend[3] = DestinationPort % 256;
    packetSend[4] = Length / 256;
    packetSend[5] = Length % 256;
    packetSend[6] = Checksum[0];
    packetSend[7] = Checksum[1];
    for (i = 0; i < Payload.size(); i++)
        packetSend[8 + i] = Payload[i];
}

void udpPacket::convertToFile()
{
    int i;
    packetFile = "";
    packetFile += CommonPacket::CharToHex((char) UDP_CODE);
    convertToSend();
    for (i = 0; i < size; i++)
    {
        packetFile.push_back(CommonPacket::CharToHex(packetSend[i] / 16));
        packetFile.push_back(CommonPacket::CharToHex(packetSend[i] % 16));
    }
}

string udpPacket::convertToRaw()
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

void udpPacket::convertFromSend()
{
    int i;
    SourcePort = packetSend[0] * 256 + packetSend[1];
    DestinationPort = packetSend[2] * 256 + packetSend[3];
    Length = packetSend[4] * 256 + packetSend[5];
    Checksum[0] = packetSend[6];
    Checksum[1] = packetSend[7];
    for (i = 8; i < size; i++)
        Payload.push_back(packetSend[i]);
}

void udpPacket::convertFromFile()
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

udpPacket::~udpPacket()
{

}
