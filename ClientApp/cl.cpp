#pragma once

#include "Includes.h"

#include "ClientSocket.h"
#include "Defines.h"

#include "Time.h"
#include <chrono>
#include <thread>
#include "Utils.h"
#include "JSON.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
        cell.setPosition(col * (cellWidth + spacing), row * (cellHeight + spacing)); 
        cell.setOutlineThickness(1.f);
        cell.setOutlineColor(sf::Color::White);
        cell.setFillColor(sf::Color::Black); 

        Symbol symbol = board[i];

        render.pWindow->draw(cell);

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
            break;
        }
    }

    render.pWindow->display();
}

// Input

int updateInput(Render render) {
    if (render.pWindow->pollEvent(*(render.pEvent))) {
        if (render.pEvent->type == sf::Event::Closed) {
            PRINT("CLOSE");
            render.pWindow->close();
        }
        if (render.pEvent->type == sf::Event::MouseButtonPressed && render.pEvent->mouseButton.button == sf::Mouse::Left) {
            PRINT("left click");
            return 1;
        }
    }
    return 0;
}

sf::Vector2i getMousePosition(Render render) {
    sf::Vector2i currentPosition = sf::Mouse::getPosition((*(render.pWindow)));
    return currentPosition;
}

//

int main() {

    ClientSocket client("127.0.0.1", 80);
    client.Connect();


    //Création d'une fenêtre
    Render myRenderer{ new sf::RenderWindow(sf::VideoMode(640, 480), "SFML"), new sf::Event, 640, 480 };

    std::array<Symbol, 9> board;
    for (int i = 0; i < 9; ++i) {
        board[i] = Symbol::Empty;
    }

    drawBoard(myRenderer, board);


    while (myRenderer.pWindow->isOpen())
    {

        int inputState = updateInput(myRenderer);
        if (inputState == 1) {
            
            sf::Vector2i mousePosition = getMousePosition(myRenderer);
            json message = CreateJsonInputMessage("Input", std::to_string(mousePosition.x), std::to_string(mousePosition.y));
            client.SendMessage(message);
        }

        ///
        
        json board = client.AwaitBroadcast();
        if (board != json::object()) {

            std::array<Symbol, 9> symbolArray;
            PrintJson(board["data"]);

            int i = 0;
            for (const auto& item : board["data"]) {

                if (item == 0) {
                    symbolArray[i] = Symbol::Empty;
                }
                else if (item == 1) {
                    symbolArray[i] = Symbol::X;
                }
                else if (item == 2) {
                    symbolArray[i] = Symbol::O;
                }

                i++;
            }

            drawBoard(myRenderer, symbolArray);
        }

    }


}







//int main() {
//    // Première connexion
//    ClientSocket client("127.0.0.1", 80);
//    client.Connect();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    ClientSocket clientt("127.0.0.1", 80);
//    clientt.Connect();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    ClientSocket clienttt("127.0.0.1", 80);
//    clienttt.Connect();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    printTimestamp();
//    std::cout << "CLIENT 3" << std::endl;
//    clienttt.SendMessage("CLIENT 3");
//
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    printTimestamp();
//    std::cout << "CLIENT 2" << std::endl;
//    clientt.SendMessage("CLIENT 2");
//
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    printTimestamp();
//    std::cout << "CLIENT 1" << std::endl;
//    client.SendMessage("CLIENT 1");
//
//    //while (true) {
//    //    client.AwaitBroadcast();
//    //    PRINT("Client 1 recu message broadcast")
//    //    clientt.AwaitBroadcast();
//    //    PRINT("Client 2 recu message broadcast")
//    //    clienttt.AwaitBroadcast();
//    //    PRINT("Client 3 recu message broadcast")
//    //}
//
//    return 0;
//}