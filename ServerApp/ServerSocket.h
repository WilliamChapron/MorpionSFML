#pragma once

#include <WinSock2.h>
#include <iostream>
#include <vector>

class ServerSocket {
public:
    ServerSocket(int port);
    ~ServerSocket();

    bool StartListening();
    SOCKET AcceptConnection();
    // Handle Many Users

    void HandleClients();

    // 

    void BroadcastMessage(const std::string& message);

    //
    void Close();

private:
    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;
};
