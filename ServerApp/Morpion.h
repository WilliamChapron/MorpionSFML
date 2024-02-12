#pragma once


#include "Includes.h"
#include <iostream>
#include <array>

enum class Symbol {
    Empty,
    X,
    O
};

struct Render;
struct Player;

class Morpion {
private:




public:
    Morpion();

    Player* currentPlayer = nullptr;

    std::array<Symbol, 9> board;

    int placeSymbol(sf::Vector2i mousePosition, int width, int height);

    bool checkHorizontalWin(Symbol playerSymbol) const;

    bool checkVerticalWin(Symbol playerSymbol) const;

    bool checkDiagonalWin(Symbol playerSymbol) const;

    bool checkBoardFull() const;

    bool checkEnd(Symbol playerSymbol) const;
};
