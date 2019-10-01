#include "ippacket.h"

ipPacket::ipPacket()
{
    int i;
    Version = 0;
    IHL = 0;
    TypeOfService = 0;
    TotalLength = 0;
    Identification = 0;
    Flags = 0;
    FragmentOffset = 0;
    TimeToLive = 0;
    Protocol = 0;
    for (i = 0; i < 4; i++)
    {
        if (i < 2)
            HeaderChecksum[i] = 0;
        SourceAddress[i] = 0;
        DestinationAddress[i] = 0;
        boxes[i] = 0;
    }
    Interface = 0;
}

ipPacket &ipPacket::operator=(const ipPacket &obj)
{
    int i;
    unsigned int tmp = obj.Version;
    Version = tmp;
    IHL = obj.IHL;
    TypeOfService = obj.TypeOfService;
    TotalLength = obj.TotalLength;
    Identification = obj.Identification;
    Flags = obj.Flags;
    FragmentOffset = obj.FragmentOffset;
    TimeToLive = obj.TimeToLive;
    Protocol = obj.Protocol;
    for (i = 0; i < 4; i++)
    {
        if (i < 2)
            HeaderChecksum[i] = obj.HeaderChecksum[i];
        SourceAddress[i] = obj.SourceAddress[i];
        DestinationAddress[i] = obj.DestinationAddress[i];
        boxes[i] = obj.boxes[i];
    }
    Options = obj.Options;
    Payload = obj.Payload;
    Interface = obj.Interface;
    return *this;
}

void ipPacket::convertToSend()
{
    int i, len;
    size = 20 + Options.size() + Payload.size();
    packetSend = (unsigned char *) malloc(size * sizeof(unsigned char));
    packetSend[0] = Version * 16 + IHL;
    packetSend[1] = TypeOfService;
    packetSend[2] = TotalLength / 256;
    packetSend[3] = TotalLength % 256;
    packetSend[4] = Identification / 256;
    packetSend[5] = Identification % 256;
    packetSend[6] = Flags * 32 + FragmentOffset / 256;
    packetSend[7] = FragmentOffset % 256;
    packetSend[8] = TimeToLive;
    packetSend[9] = Protocol;
    packetSend[10] = HeaderChecksum[0];
    packetSend[11] = HeaderChecksum[1];
    for (i = 0; i < 4; i++)
    {
        packetSend[12 + i] = SourceAddress[i];
        packetSend[16 + i] = DestinationAddress[i];
    }
    for (i = 0; i < Options.size(); i++)
        packetSend[20 + i] = Options[i];
    len = 20 + Options.size();
    for (i = 0; i < Payload.size(); i++)
        packetSend[len + i] = Payload[i];
}

void ipPacket::convertToFile()
{
    int i;
    packetFile = "";
    packetFile += CommonPacket::CharToHex((char) IP_CODE);
    for (i = 0; i < 4; i++)
        packetFile.push_back(boxes[i] ? '1' : '0');
    convertToSend();
    for (i = 0; i < size; i++)
    {
        if (i == Options.size() + 20)
        {
            packetFile.push_back('!');
            packetFile.push_back('!');
        }
        packetFile.push_back(CommonPacket::CharToHex(packetSend[i] / 16));
        packetFile.push_back(CommonPacket::CharToHex(packetSend[i] % 16));
    }
}

string ipPacket::convertToRaw()
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

void ipPacket::convertFromSend()
{
    int i;
    Version = packetSend[0] / 16;
    IHL = packetSend[0] % 16;
    TypeOfService = packetSend[1];
    TotalLength = packetSend[2] * 256 + packetSend[3];
    Identification = packetSend[4] * 256 + packetSend[5];
    Flags = packetSend[6] / 32;
    FragmentOffset = (packetSend[6] % 32) * 256 + packetSend[7];
    TimeToLive = packetSend[8];
    Protocol = packetSend[9];
    HeaderChecksum[0] = packetSend[10];
    HeaderChecksum[1] = packetSend[11];
    for (i = 0; i < 4; i++)
    {
        SourceAddress[i] = packetSend[12 + i];
        DestinationAddress[i] = packetSend[16 + i];
    }
    for (i = 20; i < ihlIndex; i++)
        Options.push_back(packetSend[i]);
    for (i = ihlIndex; i < size; i++)
        Payload.push_back(packetSend[i]);
}

void ipPacket::convertFromFile()
{
    int i, k;
    packetSend = (unsigned char *) malloc(((packetFile.size() / 2) - 3) * sizeof(unsigned char));
    k = 0;
    for (i = 1; i < 5; i++)
        boxes[i - 1] = packetFile[i] == '0' ? false : true;
    for (i = 5; i < packetFile.size(); i += 2)
        if (packetFile[i] != '!' && packetFile[i + 1] != '!')
        {
            packetSend[k] = CommonPacket::HexToChar(packetFile[i], packetFile[i + 1]);
            k++;
        }
        else
            ihlIndex = k;
    size = (packetFile.size() / 2) - 3;
    convertFromSend();
}

ipPacket::~ipPacket()
{

}
