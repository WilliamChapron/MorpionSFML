#pragma once

#include <WinSock2.h>
#include <iostream>

class ServerSocket {
public:
    ServerSocket(int port);
    ~ServerSocket();

    bool StartListening();
    SOCKET AcceptConnection();
    void Close();

private:
    int port;
    SOCKET listenSocket;
};
