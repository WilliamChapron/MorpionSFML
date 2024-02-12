#include "Morpion.h"
#include "Includes.h"

#include "Player.h"
#include <iostream>


#include "Defines.h"

Morpion::Morpion() {
    for (int i = 0; i < 9; ++i) {
        board[i] = Symbol::Empty;
    }
}

int Morpion::placeSymbol(sf::Vector2i mousePosition, int width, int height) {

    int iCol = 3;


    const float cellWidth = CALCULATE_CELL_SIZE(width, iCol, 5);
    const float cellHeight = CALCULATE_CELL_SIZE(height, iCol, 5);


    int indexX = CALCULATE_MOUSE_TO_INDEX(mousePosition.x, 5, cellWidth);
    int IndexY = CALCULATE_MOUSE_TO_INDEX(mousePosition.y, 5, cellHeight);

    int globalIndex = (IndexY * iCol) + indexX;

    PRINT(globalIndex);
    for (const auto& element : board) {
        switch (element) {
        case Symbol::X:
            std::cout << "X" << std::endl;  
            break;
        case Symbol::O:
            std::cout << "O" << std::endl; 
            break;
        case Symbol::Empty:
            std::cout << "Autre" << std::endl;  
        }
    }

    PRINT("globalIndex");
    PRINT(globalIndex);

    if (board[globalIndex] == Symbol::Empty) {
        PRINT("Empty")
            board[globalIndex] = currentPlayer->symbol;
        return 0;
    }

    PRINT("No Empty")
        return 1;



}




bool Morpion::checkHorizontalWin(Symbol playerSymbol) const {
    for (int row = 0; row < 3; ++row) {
        if (board[row * 3] == playerSymbol && board[row * 3 + 1] == playerSymbol && board[row * 3 + 2] == playerSymbol) {
            return true;
        }
    }
    return false;
}

bool Morpion::checkVerticalWin(Symbol playerSymbol) const {
    for (int col = 0; col < 3; ++col) {
        if (board[col] == playerSymbol && board[col + 3] == playerSymbol && board[col + 6] == playerSymbol) {
            return true;
        }
    }
    return false;
}

bool Morpion::checkDiagonalWin(Symbol playerSymbol) const {
    if (board[0] == playerSymbol && board[4] == playerSymbol && board[8] == playerSymbol) {
        return true;
    }
    if (board[2] == playerSymbol && board[4] == playerSymbol && board[6] == playerSymbol) {
        return true;
    }
    return false;
}

bool Morpion::checkBoardFull() const {
    for (const auto& element : board) {
        if (element == Symbol::Empty) {
            return false;
        }
    }
    return true;
}

bool Morpion::checkEnd(Symbol playerSymbol) const {
    return checkHorizontalWin(playerSymbol) || checkVerticalWin(playerSymbol) || checkDiagonalWin(playerSymbol) || checkBoardFull();
}



