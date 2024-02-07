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


class Board {
private:
    std::array<Symbol, 9> board;



public:
    Board();

    Player* currentPlayer = nullptr;

    int placeSymbol(Render render);

    void displayBoard() const; // Draw Grid
    void drawBoard(Render render) const;

    

};
