// ServerSocket.h
#pragma once

#include "Includes.h"
#include "Defines.h"
#include "JSON.h"

class App;

class ServerSocket {
public:
    ServerSocket(int port, HINSTANCE hInstance);
    ~ServerSocket();

    bool StartAsyncListening();
    void AddClientSocket(SOCKET clientSocket);
    void BroadcastMessage(const json& jsonData);
    bool isSocketAtIndex(SOCKET socketToCheck, int indexToCheck);
    void Close();

    void HandleListenSocket(App* myApp, ServerSocket* currentInstance);
    void HandleClientsSocket(App* myApp, WPARAM wParam);
    void SetPlayers(App* myApp);

    HWND hwnd;

private:
    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


};