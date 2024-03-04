#ifndef RX_CONTROL_TCP_H
#define RX_CONTROL_TCP_H
#include <winsock2.h>
#include <iostream>
#include <vector>

class TCP{

public:
    SOCKET Make_TCP_socket(std::string ip, int port);
    int Send_Command(SOCKET TCP_socket, std::vector<char> command);
    std::vector<char> Receive_Command_Reply(SOCKET TCP_socket, std::vector<char> &reply);
    SOCKET Close_Socket(SOCKET TCP_socket);


    TCP();
    ~TCP();
};

#endif //RX_CONTROL_TCP_H
