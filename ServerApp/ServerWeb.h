// ServerWeb.h
#pragma once

#include "Includes.h"
#include "Defines.h"
#include "JSON.h"


class ServerWeb {
public:
    ServerWeb(int port, HINSTANCE hInstance);
    ~ServerWeb();

    bool StartAsyncListening();
    void AddClientSocket(SOCKET clientSocket);
    void BroadcastMessage(const json& jsonData);
    void ResponseMessage(const json& jsonData);
    void Close();

private:
    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;
    HWND hwnd;
    FILE* pCout;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};