#pragma once


#include "Includes.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ClientWeb
{
public:
    ClientWeb(const char* serverIp, int serverPort);
    ~ClientWeb();

    bool Connect();
    bool SendMessageWithResponse(const json& jsonObject);
    void Close();

private:
    SOCKET clientSocket;
    sockaddr_in serverAddress;
    WSADATA wsaData;
};