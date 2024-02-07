#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "SFML/Graphics.hpp"

#include "ClientSocket.h"
#include "Defines.h"
#include "Board.h"

#include "Time.h"
#include <chrono>
#include <thread>


struct Player {
    std::string name;
    Symbol symbol;
    int score;
};

void drawBoard(Render render, std::array<Symbol, 9> board) {
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

        // Obtenez le symbole à partir du tableau board
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

void displayBoard(std::array<Symbol, 9> board) {
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

sf::Vector2i getMousePosition(Render render) {
    sf::Vector2i currentPosition = sf::Mouse::getPosition((*(render.pWindow)));
    return currentPosition;


}

int placeSymbol(Render render, std::array<Symbol, 9> board, Player* currentPlayer = nullptr) {
    sf::Vector2i mousePosition = getMousePosition(render); // Obtenez la position de la souris

    int iCol = 3;


    const float cellWidth = CALCULATE_CELL_SIZE(render.iWidth, iCol, 5);
    const float cellHeight = CALCULATE_CELL_SIZE(render.iHeight, iCol, 5);


    int indexX = CALCULATE_MOUSE_TO_INDEX(mousePosition.x, 5, cellWidth);
    int IndexY = CALCULATE_MOUSE_TO_INDEX(mousePosition.y, 5, cellHeight);

    int globalIndex = (IndexY * iCol) + indexX;

    PRINT(globalIndex);
    for (const auto& element : board) {
        switch (element) {
        case Symbol::X:
            std::cout << "X" << std::endl;  // Affiche un texte pour le symbole X
            break;
        case Symbol::O:
            std::cout << "O" << std::endl;  // Affiche un texte pour le symbole O
            break;
            // Ajoutez d'autres cas au besoin pour chaque symbole
        case Symbol::Empty:
            std::cout << "Autre" << std::endl;  // Cas par défaut si le symbole n'est pas X ou O
        }
    }

    if (board[globalIndex] == Symbol::Empty) {
        PRINT("Empty")
            board[globalIndex] = currentPlayer->symbol;
        return 0;
    }

    PRINT("No Empty")
        return 1;



}


int main(Render render, std::array<Symbol, 9> board) {
    ClientSocket client("127.0.0.1", 80);
    
    if (client.Connect()) {
        client.SendMessage("Premier message");
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    client.SendMessage("Deuxième message");



    for (int i = 0; i < 9; ++i) {
                board[i] = Symbol::Empty;
    }

    return 0;
}