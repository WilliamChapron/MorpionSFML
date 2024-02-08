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

inline json CreateJsonTable(const std::string& messageType, const std::vector<Symbol>& dataArray) {
    json message;

    // Send array 
    message["type"] = messageType;
    message["data"] = dataArray;
    message["timestamp"] = getCurrentTime();


    return message;
}


inline json ReceiveJsonFromSocket(SOCKET socket) {
    char buffer[4096];
    int bytesRead;
    std::string receivedData;

    bytesRead = recv(socket, buffer, sizeof(buffer), 0);

    if (bytesRead == -1) {
        return json::object();
    }
    else if (bytesRead <= 0) {
        // Aucune donn�e re�ue ou d�connexion du client
        return json::object();
    }
    else {
        // Donn�es re�ues avec succ�s
        receivedData += std::string(buffer, bytesRead);
        return json::parse(receivedData);
    }
}