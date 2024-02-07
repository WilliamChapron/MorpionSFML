#pragma once

#include "Time.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

json CreateJson(const std::string& messageType, const std::string& messageContent) {
    json message;

    // Ajouter le type de message
    message["type"] = messageType;

    // Ajouter le contenu du message
    message["content"] = messageContent;

    // Ajouter la date et l'heure actuelles
    message["timestamp"] = getCurrentTime();

    return message;
}