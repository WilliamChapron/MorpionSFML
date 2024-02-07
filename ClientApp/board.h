#pragma once


#include <iostream>
#include <array>

enum class Symbol {
    Empty,
    X,
    O
};

enum class Symbol;


struct Player {
    std::string name;
    Symbol symbol;
    int score;
};

struct Render;
struct Player;

class Morpion {
private:
    std::array<Symbol, 9> board;



public:
    Morpion();

    Player* currentPlayer = nullptr;

    int placeSymbol(Render render);

    void displayBoard() const; // Draw Grid
    void drawBoard(Render render) const;

    bool checkHorizontalWin(Symbol playerSymbol) const;

    bool checkVerticalWin(Symbol playerSymbol) const;

    bool checkDiagonalWin(Symbol playerSymbol) const;

    bool checkBoardFull() const;

    bool checkEnd(Symbol playerSymbol) const;
};
