#include "Morpion.h"
#include "Input.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

#include "Render.h"
#include "Defines.h"

Morpion::Morpion() {
    for (int i = 0; i < 9; ++i) {
        board[i] = Symbol::Empty;
    }
}

int Morpion::placeSymbol(int cellIndex) {
    int row = cellIndex / 3;
    int col = cellIndex % 3;

    if (board[cellIndex] == Symbol::Empty) {
        // Placer le symbole du joueur actuel dans la cellule
        board[cellIndex] = currentPlayer->symbol;
        return 0;
    }
    else {
        // La cellule n'est pas vide
        return 1;
    }
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
    // Vérification de la diagonale principale
    if (board[0] == playerSymbol && board[4] == playerSymbol && board[8] == playerSymbol) {
        return true;
    }
    // Vérification de la diagonale secondaire
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
    // Check End
    return checkHorizontalWin(playerSymbol) || checkVerticalWin(playerSymbol) || checkDiagonalWin(playerSymbol) || checkBoardFull();
}


void Morpion::displayBoard() const {
    for (size_t i = 0; i < board.size(); ++i) {
        char symbol = '-';
        if (board[i] == Symbol::X) {
            symbol = 'X';
        }
        else if (board[i] == Symbol::O) {
            symbol = 'O';
        }
        std::cout << symbol << ' ';

        if ((i + 1) % 3 == 0) {
            std::cout << std::endl;
        }
    }
    system("cls");
}


void Morpion::drawBoard(Render render) const {
    render.pWindow->clear(sf::Color::Black); // Fond noir

    const int cols = 3;
    const int rows = 3;
    const float spacing = 5.f;
    const float cellWidth = static_cast<float>(render.iWidth - (cols - 1) * spacing) / cols;
    const float cellHeight = static_cast<float>(render.iHeight - (rows - 1) * spacing) / rows;

    for (int i = 0; i < 9; ++i) {
        sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
        int row = i / cols;
        int col = i % cols;
        cell.setPosition(col * (cellWidth + spacing), row * (cellHeight + spacing)); // Ajout de l'espacement
        cell.setOutlineThickness(1.f);
        cell.setOutlineColor(sf::Color::White);
        cell.setFillColor(sf::Color::Black); // Cellules noires

        // Obtenez le symbole ŕ partir du tableau board
        Symbol symbol = board[i];

        render.pWindow->draw(cell);

        // Affichez une forme en fonction du symbole
        switch (symbol) {
        case Symbol::X: {
            sf::RectangleShape cross;
            cross.setSize(sf::Vector2f(cellWidth / 2, cellHeight / 2));
            cross.setPosition(cell.getPosition() + sf::Vector2f(cellWidth / 4, cellHeight / 4));
            cross.setFillColor(sf::Color::Red);
            render.pWindow->draw(cross);
            break;
        }
        case Symbol::O: {
            sf::CircleShape circle(std::min(cellWidth, cellHeight) / 4); // Utilisez la plus petite dimension pour le rayon
            circle.setPosition(cell.getPosition() + sf::Vector2f(cellWidth / 4, cellHeight / 4));
            circle.setFillColor(sf::Color::Blue);
            render.pWindow->draw(circle);
            break;
        }
        default:
            // Aucun symbole, vous pouvez ajouter du code pour traiter cela
            break;
        }
    }

    render.pWindow->display();
}

std::string Morpion::getBoardState() const {
    std::string state;
    for (const auto& symbol : board) {
        switch (symbol) {
        case Symbol::X:
            state += "X";
            break;
        case Symbol::O:
            state += "O";
            break;
        case Symbol::Empty:
            state += "-";
            break;
        }
    }
    return state;
}

