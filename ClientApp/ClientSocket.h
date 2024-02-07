#pragma once

#include <iostream>
#include <Winsock2.h>
#include <WS2tcpip.h> // Ajout pour inet_pton

#pragma comment(lib, "ws2_32.lib")

class ClientSocket 
{
public:
    ClientSocket(const char* serverIp, int serverPort);
    ~ClientSocket();

    bool Connect();
    bool SendMessage(const char* message);
    void AwaitBroadcast();
    void Close();

private:
    SOCKET clientSocket;
    sockaddr_in serverAddress;
    WSADATA wsaData;  
};