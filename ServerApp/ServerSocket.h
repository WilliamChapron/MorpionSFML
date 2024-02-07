#pragma once

#include "Includes.h"
#include "Defines.h"
#include <vector>
#include <string>



class ServerSocket {
public:
    ServerSocket(int port);
    ~ServerSocket();

    bool StartAsyncListening(HWND* hwnd);
    void AddClientSocket(SOCKET clientSocket, HWND* hwnd);
    void BroadcastMessage(const std::string& message);
    void Close(SOCKET clientSocket);
    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;

private:


};
