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



/*bool checkHorizontalWin(Symbol playerSymbol) {
    for (int row = 0; row < 3; ++row) {
        if (board[row * 3] == playerSymbol && board[row * 3 + 1] == playerSymbol && board[row * 3 + 2] == playerSymbol) {
            return true;
        }
    }
    return false;
    */

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




int main() {

    ClientSocket client("127.0.0.1", 80);
    client.Connect();


    //Création d'une fenêtre
    Render myRenderer{ new sf::RenderWindow(sf::VideoMode(640, 480), "SFML"), new sf::Event, 640, 480 };




    while (myRenderer.pWindow->isOpen())
    {

        int inputState = updateInput(myRenderer);
        if (inputState == 1) {
            json message = CreateJsonMessage("Input", "LeftClick");
            client.SendMessage(message);
        }


        client.AwaitBroadcast();
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