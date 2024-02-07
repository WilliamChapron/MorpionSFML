#pragma once

#include "Time.h"
#include "Includes.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;


inline json CreateJson(const std::string& messageType, const std::string& messageContent) {
    json message;

    message["type"] = messageType;
    message["content"] = messageContent;
    message["timestamp"] = getCurrentTime();

    return message;
}


inline std::string ReceiveDataJsonFromSocket(SOCKET socket) {
    std::string receivedData;
    char buffer[4024];
    int bytesRead;

    while (true) {
        bytesRead = recv(socket, buffer, sizeof(buffer), 0);

        if (bytesRead == 0) {
            return "null";
        }
        if (bytesRead > 0) {
            receivedData += std::string(buffer, bytesRead);
        }
    }

    return receivedData;
}