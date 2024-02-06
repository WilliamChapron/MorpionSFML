#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <string>

#define WM_SOCKET (WM_USER + 1)

class ServerSocket {
public:
    ServerSocket(int port);
    ~ServerSocket();

    bool StartAsyncListening(HWND hwnd);
    void HandleClients();
    void BroadcastMessage(const std::string& message);
    void Close();

private:
    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;
};
