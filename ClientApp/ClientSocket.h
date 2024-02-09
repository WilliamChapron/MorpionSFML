#pragma once


#include "Includes.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ClientSocket
{
public:
    ClientSocket(const char* serverIp, int serverPort);
    ~ClientSocket();

    bool Connect();
    bool SendMessage(const json& jsonObject);
    json AwaitBroadcast();
    void Close();

private:
    SOCKET clientSocket;
    sockaddr_in serverAddress;
    WSADATA wsaData;
};