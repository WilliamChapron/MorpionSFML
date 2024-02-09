
#include "Render.h"
#include "Morpion.h"



#include "Includes.h"
#include "ServerSocket.h"
#include "Defines.h"
#include "GameManager.h"
//#include "SetPlayers.h"
#include "Morpion.h"

#include "Time.h"

#include "Player.h"

#include "ServerSocket.h"

#include <iostream>
#include <fstream>
#include <sstream>


#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "JSON.h";


HWND* g_hwnd = nullptr;
ServerSocket* g_pServer = nullptr;
Morpion* g_myMorpion = nullptr;
int g_turnCounter = 0;
Player* player1 = nullptr;
Player* player2 = nullptr;
int playerNumber = 0;




bool turn(sf::Vector2i mousePosition) {
    int placeState = g_myMorpion->placeSymbol(mousePosition, 640, 480);
    if (placeState == 1) {
        std::cout << "Erreur de placement du symbole. Impossible de placer à cet emplacement." << std::endl;
        return false;
    }

    std::cout << "Tour " << g_turnCounter << ": ";
    std::cout << "Joueur actuel : " << g_myMorpion->currentPlayer->name << ", Symbole : " << static_cast<char>(g_myMorpion->currentPlayer->symbol) << std::endl;

    // Draw
    json boardJson = CreateJsonTable("Message", g_myMorpion->board);
    g_pServer->BroadcastMessage(boardJson);

    return true;
}




LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_LISTEN_SOCKET:
    {
        while (true) {
            SOCKET newClientSocket = accept(g_pServer->listenSocket, nullptr, nullptr);
            if (newClientSocket == INVALID_SOCKET) {
                break;
            }


            if (player1 == nullptr || player2 == nullptr) {
                if (player1 == nullptr && player2 == nullptr) {
                    PRINT("Set player1");
                    player1 = new Player("Player1", Symbol::X, 0);
                    g_myMorpion->currentPlayer = player1;
                }
                else if (player1 != nullptr && player2 == nullptr) {
                    PRINT("Set player2");
                    player2 = new Player("Player2", Symbol::O, 0);
                }


            }
            else {
                break;
            }

            // #TODO disconnect parceque on veut pas etablir la connexion
            printTimestamp();
            std::cout << "Nouvelle connexion établie." << std::endl;
            g_pServer->AddClientSocket(newClientSocket, g_hwnd);

            




            
        }
        break;
    }
    case WM_CLIENTS_SOCKET:
    {


        SOCKET clientSocket = static_cast<SOCKET>(wParam);

        json receivedJson = ReceiveJsonFromSocket(clientSocket);

        if (!receivedJson.empty()) {

            sf::Vector2i mousePosition = {
                std::stoi(receivedJson["x"].get<std::string>()),
                std::stoi(receivedJson["y"].get<std::string>())
            };

            PRINT(mousePosition.x);
            PRINT(mousePosition.y);
            turn(mousePosition);

            if (g_myMorpion->checkEnd(Symbol::X) || g_myMorpion->checkEnd(Symbol::O)) {
                //PRINT("Partie terminé, joueur gagnant :")
                //PRINT(myMorpion->currentPlayer->name);
                //break;
            }

             //Transition next it
            g_myMorpion->currentPlayer = (g_turnCounter % 2 == 0) ? player2 : player1;
            g_turnCounter++;
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
    freopen_s(&pCout, "CONOUT$", "w", stdout); 


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

    g_hwnd = &hwnd; 

    ShowWindow(hwnd, SW_HIDE);

    // Initialiser et démarrer le serveur
    g_pServer = new ServerSocket(80);
    if (!g_pServer->StartAsyncListening(g_hwnd)) {
        return 0;
    }

    g_myMorpion = new Morpion();
    g_myMorpion->currentPlayer = player1;



    //std::vector<Symbol> table = { Symbol::X, Symbol::O, Symbol::Empty};
    //json array = CreateJsonTable("Message", table);
    //json message = CreateJsonMessage("Message", "Hello");

    float startTime = getCurrentTime();
    bool isBroadcasted = false;

    MSG msg = {};
    while (true) {
        //test json

        //test json
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            // #CAN we can call any function here if we wish in mainLoop
        }
        //if (getCurrentTime() > startTime + 5 && !isBroadcasted) {
        //    PRINT("Broadcast message");
        //    g_pServer->BroadcastMessage(array);
        //    isBroadcasted = true;
        //}
    }
    

    fclose(pCout); 
    FreeConsole(); 

    return 0;
}





// #TODO Send Failed to client with send
            // #TODO Handle when client disconnected
            // #TODO Handle Broadcast to all clients
            // #NOW bidirectional request, request and response + connection timed out working