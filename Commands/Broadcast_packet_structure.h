#ifndef RX_CONTROL_BROADCAST_PACKET_STRUCTURE_H
#define RX_CONTROL_BROADCAST_PACKET_STRUCTURE_H

#include <string>
#pragma once
#pragma pack(push, 1)

struct DevBroadcastInf_CLB
{
    uint8_t id;
    uint16_t modification;
    int port;
    const char* ip_str;
    const char* str_name;
    const char* firmware;
};

#pragma pack(pop)

#endif //RX_CONTROL_BROADCAST_PACKET_STRUCTURE_H

