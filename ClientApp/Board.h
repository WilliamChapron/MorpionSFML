#pragma once


#include <iostream>
#include <array>

enum class Symbol {
    Empty,
    X,
    O
};

namespace sf {
    class RenderWindow;
    class Event;
}



struct Render {
    sf::RenderWindow* pWindow;
    sf::Event* pEvent;
    int iWidth;
    int iHeight;
    // Update SFML Render
};


struct Player {
    std::string name;
    Symbol symbol;
    int score;
};


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

int updateInput(Render render);

