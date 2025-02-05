#pragma once

#include <string> // Inclure la bibliothèque pour std::string


#include "Morpion.h"
#include "Defines.h"

enum class Symbol;

struct Player {
    std::string name;
    Symbol symbol;
    int score;

    // Constructeur  arguments "name" "symbol" "score"
    Player(const std::string& playerName, Symbol playerSymbol, int playerScore) : name(playerName), symbol(playerSymbol), score(playerScore) {}
};