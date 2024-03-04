#include "TCP.h"

TCP::TCP() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cout << "WSAStartup failed: " << result << std::endl;
        return;
    }
}

TCP::~TCP() {
    WSACleanup();
}

SOCKET TCP::Make_TCP_socket(std::string ip, int port) {
    sockaddr_in sock_addr;

    SOCKET _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == INVALID_SOCKET) {
        std::cout << "Socket creation error " << WSAGetLastError() << std::endl;
        return INVALID_SOCKET;
    }

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);

    // Convert IP address to network byte order
    sock_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    if (sock_addr.sin_addr.s_addr == INADDR_NONE) {
        std::cout << "Invalid IP address" << std::endl;
        closesocket(_socket);
        return INVALID_SOCKET;
    }

    // Set non-blocking mode
    unsigned long ulMode = 1;
    if (ioctlsocket(_socket, FIONBIO, &ulMode) != 0) {
        std::cout << "Failed to set non-blocking mode" << std::endl;
        closesocket(_socket);
        return INVALID_SOCKET;
    }

    // Initiate connection
    if (connect(_socket, (sockaddr*)&sock_addr, sizeof(sock_addr)) == SOCKET_ERROR) {
        int connectError = WSAGetLastError();
        if (connectError != WSAEWOULDBLOCK) {
            std::cout << "Socket connection error " << connectError << std::endl;
            closesocket(_socket);
            return INVALID_SOCKET;
        }
    }

    // Wait for connection completion

    // Disable non-blocking mode
    ulMode = 0;
    if (ioctlsocket(_socket, FIONBIO, &ulMode) != 0) {
        std::cout << "Failed to set blocking mode" << std::endl;
        closesocket(_socket);
        return INVALID_SOCKET;
    }

    return _socket;
}

int TCP::Send_Command(SOCKET TCP_socket, std::vector<char> command) {
    sockaddr_in sockAddress_in;
    int len_t = sizeof(sockAddress_in);
    int lenSendMess=0;

    lenSendMess = sendto(TCP_socket, command.data(), sizeof(command), 0, (struct sockaddr*)&sockAddress_in, len_t);
    if (lenSendMess == -1)
    {
        std::cout << "Send error " << WSAGetLastError() << std::endl;
    }
    return lenSendMess;
}

std::vector<char> TCP::Receive_Command_Reply(SOCKET TCP_socket, std::vector<char> &reply) {
    struct sockaddr_in addr_in;
    int len_addr = sizeof(addr_in);
    int len = recvfrom(TCP_socket, reply.data(), sizeof(reply), 0, (sockaddr*)&addr_in, &len_addr);
    if (len == SOCKET_ERROR)
    {
        std::cout << "Receive error " << WSAGetLastError() << std::endl;
//        return [];
    }
    return reply;
}

SOCKET TCP::Close_Socket(SOCKET TCP_socket) {

    closesocket(TCP_socket);
    WSACleanup();
    return 0;
}
