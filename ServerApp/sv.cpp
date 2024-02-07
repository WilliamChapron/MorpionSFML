
//#include <SFML/Graphics.hpp>
//#include "Render.h"
//#include "Input.h"
//#include "Player.h"
//#include "Defines.h"



#include "Includes.h"
#include "ServerSocket.h"
#include "Defines.h"
#include "GameManager.h"
#include "SetPlayers.h"
#include "Morpion.h"

#include "Time.h"

#include "ServerSocket.h"

#include <iostream>
#include <fstream>



//bool turn(Render render, Morpion* morpion, int turnCounter) {
//    int placeState = morpion->placeSymbol(render);
//    if (placeState == 1) {
//        std::cout << "Erreur de placement du symbole. Impossible de placer à cet emplacement." << std::endl;
//        return false;
//    }
//
//    std::cout << "Tour " << turnCounter << ": ";
//    std::cout << "Joueur actuel : " << morpion->currentPlayer->name << ", Symbole : " << static_cast<char>(morpion->currentPlayer->symbol) << std::endl;
//
//    morpion->drawBoard(render);
//
//    return true;
//}



Morpion morpion;

HWND* g_hwnd = nullptr;
ServerSocket* g_pServer = nullptr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_LISTEN_SOCKET:
    {
        while (true) {
            SOCKET newClientSocket = accept(g_pServer->listenSocket, nullptr, nullptr);
            if (newClientSocket == INVALID_SOCKET) {
                // Aucun nouveau client en attente, sortie de la boucle
                break;
            }

            printTimestamp();
            std::cout << "Nouvelle connexion établie." << std::endl;
            g_pServer->AddClientSocket(newClientSocket, g_hwnd);

            // Créer un joueur pour chaque nouveau client
            Player* client = new Player("Client", Symbol::X, 1);

            // Appeler la fonction SetPlayersFromClients pour configurer les joueurs dans GameManager
            SetPlayersFromClients(client, client);
        }
        break;
    }

    case WM_CLIENTS_SOCKET:
    {

        // Récupérer le socket du client à partir de wParam
        SOCKET clientSocket = static_cast<SOCKET>(wParam);

        // Vérifier s'il y a des données à lire sur le socket
        char buffer[4024];
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead > 0) {
            // Des données ont été lues, traitez-les comme nécessaire
            std::string receivedData(buffer, bytesRead);
            printTimestamp();
            std::cout << "Received data from client : " << receivedData << std::endl;

            // Exemple: Envoyer un message de retour
            std::string response = "Server successfully received : " + receivedData;
            send(clientSocket, response.c_str(), response.size(), 0);

            // Envoi de la grille mise à jour à tous les clients
            std::string gameState = morpion.getBoardState();
            for (auto& client : g_pServer->clientSockets) {
                send(client, gameState.c_str(), gameState.size(), 0);
            }
        }
        else if (bytesRead == 0) {
            std::cout << "Nothing received from client : " << std::endl;
            // #TODO Send Failed to client with send
            // #TODO Handle when client disconnected
            // #TODO Handle Broadcast to all clients
            // #NOW bidirectional request, request and response + connection timed out working

        }
        else {
            // Erreur de lecture du socket, gestion des erreurs si nécessaire
            int errorCode = WSAGetLastError();
            if (errorCode != WSAEWOULDBLOCK) {
                std::cerr << "Socket error: " << errorCode << std::endl;
            }
        }
        break;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AllocConsole(); // Créer une nouvelle console
    FILE* pCout;
    freopen_s(&pCout, "CONOUT$", "w", stdout); // Rediriger la sortie standard vers la console

    // Créer la fenêtre
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ServerWindowClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        L"ServerWindowClass",
        L"Server App",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        0,
        0,
        hInstance,
        0);

    if (!hwnd)
        return -1;

    g_hwnd = &hwnd; // Affecter l'adresse de hwnd à g_hwnd

    ShowWindow(hwnd, SW_SHOW);

    // Initialiser et démarrer le serveur
    g_pServer = new ServerSocket(80);
    if (!g_pServer->StartAsyncListening(g_hwnd)) {
        // Gérer l'échec de démarrage du serveur
        return -1;
    }

    // Utiliser une boucle simple pour maintenir l'application active
    MSG msg = {};
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // #CAN we can call any function here if we wish in mainLoop
    }

    fclose(pCout); // Fermer la redirection de la sortie standard
    FreeConsole(); // Fermer la console

    return 0;
}


////MORPION BASIC
//int main(int argc, char** argv)
//{
//
//    std::cout << "SERVER" << std::endl;
//    
//
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        std::cerr << "Failed to initialize Winsock." << std::endl;
//        return 1;
//    }
//
//    ServerSocket server(80);
//    if (server.StartListening()) {
//        server.HandleClients();
//    }
//
//    return 0;
//
//
//
//
//
//
//    ////Création d'une fenêtre
//    //Render myRenderer{new sf::RenderWindow(sf::VideoMode(640, 480), "SFML"), new sf::Event, 640, 480};
//    //Morpion* myMorpion;
//    //myMorpion = new Morpion;
//
//    //Player* player1 = nullptr;
//    //player1 = new Player{ "William", Symbol::X, 0};
//
//    //Player* player2 = nullptr;
//    //player2 = new Player{ "Bot", Symbol::O, 0 };
//
//
//    ////GameLoop
//    //myMorpion->drawBoard(myRenderer);
//    //myMorpion->currentPlayer = player1;
//    //int turnCounter = 0;
//    //while (myRenderer.pWindow->isOpen())
//    //{
//
//    //    
//
//
//    //    //EVENT
//    //    int inputState = updateInput(myRenderer);
//    //    //PRINT(myMorpion.currentPlayer->name)
//    //    if (inputState == 0) {
//    //        //PRINT("Pas d'Input")
//    //        continue;
//    //    }
//    //    else if(inputState == 1) {
//    //        if (!turn(myRenderer, myMorpion, turnCounter))
//    //        {
//    //            continue;
//    //        };
//    //    }
//
//
//
//
//   
//
//
//
//    //    //PRINT("Action")
//
//    //    //UPDATE
//
//    //    //DRAW
//    //    if (myMorpion->checkEnd(Symbol::X) || myMorpion->checkEnd(Symbol::O)) {
//    //        PRINT("Partie terminé, joueur gagnant :")
//    //        PRINT(myMorpion->currentPlayer->name);
//    //        //break;
//    //    }
//
//    //    // Transition next it
//    //    myMorpion->currentPlayer = (turnCounter % 2 == 0) ? player2 : player1;
//    //    turnCounter++;
//
//
//    //}
//
//    return 0;
//}
