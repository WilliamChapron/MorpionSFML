#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "ClientSocket.h"
#include "Defines.h"

#include "Time.h"
#include <chrono>
#include <thread>
#include "Board.h"
#include <SFML/Graphics.hpp>


int main(Render render, Morpion* morpion){

    /*ClientSocket client("127.0.0.1", 80);
    
    if (client.Connect()) {
        client.SendMessage("Premier message");
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    client.SendMessage("Deuxième message");
    */
   

    //Création d'une fenêtre
    Render myRenderer{new sf::RenderWindow(sf::VideoMode(640, 480), "SFML"), new sf::Event, 640, 480};
    Morpion* myMorpion;
    myMorpion = new Morpion;

    Player* player1 = nullptr;
    player1 = new Player{ "William", Symbol::X, 0};
    
    Player* player2 = nullptr;
    player2 = new Player{ "Bot", Symbol::O, 0 };


    //GameLoop
    myMorpion->drawBoard(myRenderer);
    myMorpion->currentPlayer = player1;
    int turnCounter = 0;
    while (myRenderer.pWindow->isOpen())
    {

    //    


    //EVENT
    int inputState = updateInput(myRenderer);
    sf::Vector2i getMousePosition(Render render);
    PRINT(myMorpion.currentPlayer->name)
        if (inputState == 0) {
            //PRINT("Pas d'Input")
            continue;
        }
        else if(inputState == 1) {
            if (!turn(myRenderer, myMorpion, turnCounter))
            {
                continue;
            };
        }








        //PRINT("Action")

        //UPDATE

        //DRAW
        if (myMorpion->checkEnd(Symbol::X) || myMorpion->checkEnd(Symbol::O)) {
            PRINT("Partie terminé, joueur gagnant :")
            PRINT(myMorpion->currentPlayer->name);
            //break;
        }

        // Transition next it
        myMorpion->currentPlayer = (turnCounter % 2 == 0) ? player2 : player1;
        turnCounter++;

    return 0;


   // Render myRenderer{ new sf::RenderWindow}
   //morpion->drawBoard(render);


    return 0;
}