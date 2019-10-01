#include "tcppacket.h"

tcpPacket::tcpPacket()
{
    SourcePort = 0;
    DestinationPort = 0;
    SequenceNumber = 0;
    AcknowledgmentNumber = 0;
    DataOffset = 0;
    Reserved = 0;
    Flags = 0;
    Window = 0;
    Checksum[0] = 0;
    Checksum[1] = 0;
    UrgentPointer = 0;
    Interface = 0;
    boxes[0] = 0;
    boxes[1] = 0;
}

tcpPacket &tcpPacket::operator=(const tcpPacket &obj)
{
    int i;
    SourcePort = obj.SourcePort;
    DestinationPort = obj.DestinationPort;
    SequenceNumber = obj.SequenceNumber;
    AcknowledgmentNumber = obj.AcknowledgmentNumber;
    DataOffset = obj.DataOffset;
    Reserved = obj.Reserved;
    Flags = obj.Flags;
    Window = obj.Window;
    Checksum[0] = obj.Checksum[0];
    Checksum[1] = obj.Checksum[1];
    UrgentPointer = obj.UrgentPointer;
    Options = obj.Options;
    Payload = obj.Payload;
    Interface = obj.Interface;
    boxes[0] = obj.boxes[0];
    boxes[1] = obj.boxes[1];
    return *this;
}

void tcpPacket::convertToSend()
{
    int i, len;
    size = 20 + Options.size() + Payload.size();
    packetSend = (unsigned char *) malloc(size * sizeof(unsigned char));
    packetSend[0] = SourcePort / 256;
    packetSend[1] = SourcePort % 256;
    packetSend[2] = DestinationPort / 256;
    packetSend[3] = DestinationPort % 256;
    packetSend[4] = (SequenceNumber / 65536) / 256;
    packetSend[5] = (SequenceNumber / 65536) % 256;
    packetSend[6] = (SequenceNumber % 65536) / 256;
    packetSend[7] = (SequenceNumber % 65536) % 256;
    packetSend[8] = (AcknowledgmentNumber / 65536) / 256;
    packetSend[9] = (AcknowledgmentNumber / 65536) % 256;
    packetSend[10] = (AcknowledgmentNumber % 65536) / 256;
    packetSend[11] = (AcknowledgmentNumber % 65536) % 256;
    packetSend[12] = DataOffset * 16 + Reserved / 4;
    packetSend[13] = (Reserved % 4) * 64 + Flags;
    packetSend[14] = Window / 256;
    packetSend[15] = Window % 256;
    packetSend[16] = Checksum[0];
    packetSend[17] = Checksum[1];
    packetSend[18] = UrgentPointer / 256;
    packetSend[19] = UrgentPointer % 256;
    for (i = 0; i < Options.size(); i++)
        packetSend[20 + i] = Options[i];
    len = 20 + Options.size();
    for (i = 0; i < Payload.size(); i++)
        packetSend[len + i] = Payload[i];
}

void tcpPacket::convertToFile()
{
    int i;
    packetFile = "";
    packetFile += CommonPacket::CharToHex((char) TCP_CODE);
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

string tcpPacket::convertToRaw()
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

void tcpPacket::convertFromSend()
{
    int i;
    SourcePort = packetSend[0] * 256 + packetSend[1];
    DestinationPort = packetSend[2] * 256 + packetSend[3];
    SequenceNumber = (packetSend[4] * 256 + packetSend[5]) * 65536 + packetSend[6] * 256 + packetSend[7];
    AcknowledgmentNumber = (packetSend[8] * 256 + packetSend[9]) * 65536 + packetSend[10] * 256 + packetSend[11];
    DataOffset = packetSend[12] / 16;
    Reserved = (packetSend[12] % 16) * 4 + packetSend[13] / 64;
    Flags = packetSend[13] % 64;
    Window = packetSend[14] * 256 + packetSend[15];
    Checksum[0] = packetSend[16];
    Checksum[1] = packetSend[17];
    UrgentPointer = packetSend[18] * 256 + packetSend[19];
    for (i = 20; i < ihlIndex; i++)
        Options.push_back(packetSend[i]);
    for (i = ihlIndex; i < size; i++)
        Payload.push_back(packetSend[i]);
}

void tcpPacket::convertFromFile()
{
    int i, k;
    packetSend = (unsigned char *) malloc(((packetFile.size() / 2 ) - 1) * sizeof(unsigned char));
    k = 0;
    for (i = 1; i < packetFile.size(); i += 2)
        if (packetFile[i] != '!' && packetFile[i + 1] != '!')
        {
            packetSend[k] = CommonPacket::HexToChar(packetFile[i], packetFile[i + 1]);
            k++;
        }
        else
            ihlIndex = k;
    size = packetFile.size() / 2 - 1;
    convertFromSend();
}

tcpPacket::~tcpPacket()
{

}
