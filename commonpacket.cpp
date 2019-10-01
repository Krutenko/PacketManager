#include "commonpacket.h"

CommonPacket::CommonPacket()
{

}

unsigned char CommonPacket::HexToChar(unsigned char h, unsigned char l)
{
    unsigned char res = 0;
    if (h >= '0' && h <= '9')
        res += h - '0';
    else if (h >= 'a' && h <= 'f')
        res += h - 'a' + 10;
    else if (h >= 'A' && h <= 'F')
        res += h - 'A' + 10;
    else
        return '!';
    res *= 16;
    if (l >= '0' && l <= '9')
        res += l - '0';
    else if (l >= 'a' && l <= 'f')
        res += l - 'a' + 10;
    else if (l >= 'A' && l <= 'F')
        res += l - 'A' + 10;
    else
        return '!';
    return res;
}

unsigned char CommonPacket::CharToHex(unsigned char c)
{
    unsigned char res;
    if (c >= 16)
        res = '!';
    if (c >= 0 && c <= 9)
        res = c + '0';
    else if (c >= 10)
        res = c - 10 + 'A';
    return res;
}

char *CommonPacket::iptos(unsigned long in)
{
    static char output[IPTOSBUFFERS][3*4+3+1];
    static short which;
    unsigned char *p;
    p = (unsigned char *)&in;
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
    _snprintf_s(output[which], sizeof(output[which]), sizeof(output[which]),"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];
}
