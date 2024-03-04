#include "Commands.h"

std::vector<char> Commands::Get_Status() {
    header_req packet;
    packet.cmd_type = 0x1;
    packet.messid = 1;
    packet.size = sizeof(packet);

    std::vector<char> command(sizeof(packet));
    memcpy(command.data(), &packet, sizeof(packet));
    return command;
}

int Commands::Set_Freq(uint32_t freq) {

}

int Commands::Get_IQ() {

}
