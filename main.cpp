#include <math.h>
#include "Commands/Broadcast_packet_structure.h"
#include "TCP/TCP.h"
#include "UDP/UDP.h"
#include "Commands/Commands.h"
#include <string>

int main() {

    //Создаем объекты классов
    Commands get_status;
    TCP TCP_socket;

    int port = 42000;
    std::string ip = "192.168.40.255";
    SOCKET command_socket = TCP_socket.Make_TCP_socket(ip, port);
    createUDPSocketAndBindWithDefineIpAndFreePort(ip, port);
    TCP_socket.Send_Command(command_socket, get_status.Get_Status());
    std::vector<char> reply (sizeof(status_data));
    status_data command_reply;
    TCP_socket.Receive_Command_Reply(command_socket, reply);
    memcpy(&reply, &command_reply, sizeof(command_reply));

    //Выводим данные на экран

    std::cout << "Is sucsess: " << command_reply.cmd_complete << std::endl;
    std::cout << "Antenna: " << static_cast<int>(command_reply.ant) << std::endl;
    Sleep(800);
    std::cout << "Sample rate: " << command_reply.sample_rate_Hz / std::pow(10, 3) << " kHz" << std::endl;
    std::cout << "Carrier frequency: " << command_reply.carrier_freq_Hz / std::pow(10, 3) << " kHz" << std::endl;



    closesocket(command_socket);
//    closesocket(recvSocket);
    WSACleanup();
    return 0;
}
