#pragma once

#include <WinSock2.h>
#include <iostream>
#include <vector>

class GameManager; // Forward declaration de GameManager

class ServerSocket {
public:
    ServerSocket(int port);
    ~ServerSocket();

    bool StartListening();
    SOCKET AcceptConnection();
    void HandleClients(GameManager& gameManager); // Modifier pour accepter un GameManager
    void BroadcastMessage(const std::string& message);
    void Close();

private:
    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;
};