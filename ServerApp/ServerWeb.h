// ServerWeb.h
#pragma once

#include "Includes.h"
#include "Defines.h"
#include "JSON.h"

// Structure de données pour les journaux
struct WebLog {
    std::string action;
    std::string player;
    std::string symbol;
    std::string time;
};


class ServerWeb {
public:
    ServerWeb(int port, HINSTANCE hInstance);
    ~ServerWeb();

    bool StartAsyncListening();
    void AddClientSocket(SOCKET clientSocket);
    void ResponseRequest(SOCKET clientSocket);
    void Close();

    HWND hwnd;

private:
    int port;
    SOCKET listenSocket;
    std::vector<SOCKET> clientSockets;

    FILE* pCout;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};