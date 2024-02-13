#pragma once

#include "Time.h"
#include "Includes.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;
enum class Symbol;

inline void PrintJson(const json& jsonObject) {
    std::cout << jsonObject.dump() << std::endl;
}

inline json CreateJsonMessage(const std::string& messageType, const std::string& messageContent) {
    json message;


    // Send message
    message["type"] = messageType;
    message["content"] = messageContent;
    message["timestamp"] = getCurrentTime();


    return message;
}

inline json CreateJsonTable(const std::string& messageType, const std::array<Symbol, 9>& dataArray) {
    json message;

    // Send array 
    message["type"] = messageType;
    message["data"] = dataArray;
    message["timestamp"] = getCurrentTime();


    return message;
}


json ReceiveJsonFromSocket(SOCKET socket) {
    char buffer[4096];
    int bytesRead;
    std::string receivedData;

    // while (true) {
    bytesRead = recv(socket, buffer, sizeof(buffer), 0);

    if (bytesRead <= 0) {
        return json::object();
    }

    receivedData += std::string(buffer, bytesRead);
    return json::parse(receivedData);
    //}
}