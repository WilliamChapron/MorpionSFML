

#include "Morpion.h"

#include "App.h"

#include "Includes.h"
#include "ServerSocket.h"
#include "Defines.h"
#include "Morpion.h"

#include "Time.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <sstream>


//#include <nlohmann/json.hpp>
//using json = nlohmann::json;
//#include "JSON.h";

//void handlePlayerAction(Player* player, Render render) {
//    if (player == currentPlayer) {
//        int placeState = morpion.placeSymbol(render);
//        if (placeState == 0) {
//            currentPlayer = (currentPlayer == player1) ? player2 : player1; // switch joueur après chaque coup
//            // Maintenant, vous pouvez envoyer les mises à jour de l'état du jeu aux clients ici
//        }
//    }
//}
//
//

    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
        App* myApp = App::GetInstance();
        myApp->Init(hInstance);

        myApp->Run();

        delete myApp;

        return 0;
    }



// #TODO Send Failed to client with send
// #TODO Handle when client disconnected
// #TODO Handle Broadcast to all clients
// #NOW bidirectional request, request and response + connection timed out working