#pragma once

#include <string> // Assurez-vous d'inclure l'en-tête pour std::string
#include "Defines.h" // Assurez-vous que Symbol est inclus depuis Defines.h

struct Player {
    std::string name;
    Symbol symbol;
    int score;

    // Constructeur par défaut
    Player() : name(""), symbol(Symbol::Empty), score(0) {}

    // Constructeur avec initialisation de tous les membres
    Player(const std::string& playerName, Symbol playerSymbol, int playerScore)
        : name(playerName), symbol(playerSymbol), score(playerScore) {}
};
