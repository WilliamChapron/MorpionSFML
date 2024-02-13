// ServerSocket.h
#pragma once

#include "Includes.h"
#include "Defines.h"
#include "JSON.h"

//#include <nlohmann/json.hpp>
//using json = nlohmann::json;

class ServerSocket {
public:
    ServerSocket(int port, HINSTANCE hInstance);
    ~ServerSocket();

    bool StartAsyncListening();
    void AddClientSocket(SOCKET clientSocket);
    void BroadcastMessage(const json& jsonData);
    bool isSocketAtIndex(SOCKET socketToCheck, int indexToCheck);
    void Close();

private:
    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;
    HWND hwnd;
    FILE* pCout;

    public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};