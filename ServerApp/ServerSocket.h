#pragma once

#include "Includes.h"
#include "Defines.h"
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


class ServerSocket {
public:
    ServerSocket(int port);
    ~ServerSocket();

    bool StartAsyncListening(HWND* hwnd);
    void AddClientSocket(SOCKET clientSocket, HWND* hwnd);
    void BroadcastMessage(const json& jsonData);

    bool isSocketAtIndex(SOCKET socketToCheck, int indexToCheck);

    void Close(SOCKET clientSocket);


    // var

    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;

private:


};