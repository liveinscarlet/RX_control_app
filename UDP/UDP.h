#ifndef RX_CONTROL_UDP_H
#define RX_CONTROL_UDP_H
#include <winsock2.h>
inline int createUDPSocketAndBindWithDefineIpAndFreePort(std::string ip_str, int& port)
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cout << "WSAStartup failed: " << result << std::endl;
        return -1;
    }
    SOCKET _socket;
    //Create socket
    if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        return -1;
    }

    //Address
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = 0;
    dest_addr.sin_addr.s_addr = inet_addr(ip_str.c_str());

    //binding a socket to a local address
    if (bind(_socket, (sockaddr*)&dest_addr, sizeof(dest_addr)) < 0)
    {
        return -1;
    }

    //get the local address
    int my_addr_size = sizeof(dest_addr);
    getsockname(_socket, (sockaddr*)&dest_addr, &my_addr_size);
    port = ntohs(dest_addr.sin_port);
    return _socket;
}



#endif //RX_CONTROL_UDP_H
