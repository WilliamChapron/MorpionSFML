
//#include <SFML/Graphics.hpp>
//#include "Render.h"
//#include "Input.h"
//#include "Morpion.h"
//#include "Player.h"
//#include "Defines.h"

//


#include "Includes.h"
#include "ServerSocket.h"
#include "Defines.h"


#include "Time.h"

#include "ServerSocket.h"

#include <iostream>
#include <fstream>

//


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
            std::string receivedData(buffer, bytesRead);
            printTimestamp();
            std::cout << "Received data from client : " << receivedData << std::endl;

            // Send return message
            //std::string response = "Server successfully received : " + receivedData;
            //send(clientSocket, response.c_str(), response.size(), 0);
        }
        else if (bytesRead == 0) {
            std::cout << "Nothing received from client : " << std::endl;
            // #TODO Send Failed to client with send
            // #TODO Handle when client disconnected
            // #TODO Handle Broadcast to all clients
            // #NOW bidirectional request, request and response + connection timed out working

        }
        else {
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



    const char* broadcastMessage = "Salut tout les clients c'est moi";
    float startTime = getCurrentTime();
    bool isBroadcasted = false;

    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            // #CAN we can call any function here if we wish in mainLoop
        }
        if (getCurrentTime() > startTime + 5 && !isBroadcasted) {
            PRINT("Broadcast message");
            g_pServer->BroadcastMessage(broadcastMessage);
            isBroadcasted = true;
        }
    }
    

    fclose(pCout); 
    FreeConsole(); 

    return 0;
}



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

//#include <iostream>
//#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
//#include <WinSock2.h>
// 
// 
//
//#pragma comment(lib, "ws2_32.lib")
//
//struct ConnectionData {
//    WSADATA wsaData;
//    SOCKET clientSocket;
//    sockaddr_in serverAddress;
//    const char* getRequest;
//};
//
//// Init Connexion
//bool InitializeConnection(ConnectionData& connectionData) {
//    // Init Winsock
//    if (WSAStartup(MAKEWORD(2, 2), &connectionData.wsaData) != 0) {
//        std::cerr << "Erreur lors de l'initialisation de Winsock." << std::endl;
//        return false;
//    }
//
//    // Init Client Socket
//    connectionData.clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    if (connectionData.clientSocket == INVALID_SOCKET) {
//        std::cerr << "Erreur lors de la création du socket." << std::endl;
//        WSACleanup();
//        return false;
//    }
//
//    // Config Server Address
//    inet_pton(AF_INET, "172.217.169.78", &(connectionData.serverAddress.sin_addr));
//    connectionData.serverAddress.sin_family = AF_INET; // IP V4
//    connectionData.serverAddress.sin_port = htons(80); // Port 80
//
//    // Connect Client Socket to server address
//    if (connect(connectionData.clientSocket, reinterpret_cast<sockaddr*>(&connectionData.serverAddress), sizeof(connectionData.serverAddress)) == SOCKET_ERROR) {
//        std::cerr << "Erreur lors de la connexion au serveur." << std::endl;
//        closesocket(connectionData.clientSocket);
//        WSACleanup();
//        return false;
//    }
//
//    std::cout << "Connexion établie ..." << std::endl;
//    return true;
//}
//
//// Send Request
//bool SendRequest(ConnectionData& connectionData) {
//    if (send(connectionData.clientSocket, connectionData.getRequest, strlen(connectionData.getRequest), 0) == SOCKET_ERROR) {
//        std::cerr << "Erreur lors de l'envoi de la requête." << std::endl;
//        closesocket(connectionData.clientSocket);
//        WSACleanup();
//        return false;
//    }
//
//    return true;
//}
//
//
//void ReceiveAndDisplayResponse(ConnectionData& connectionData) {
//    char buffer[4096];
//    int bytesRead;
//    while ((bytesRead = recv(connectionData.clientSocket, buffer, sizeof(buffer), 0)) > 0) {
//        std::cout.write(buffer, bytesRead);
//    }
//}
//
//
//void CloseConnection(ConnectionData& connectionData) {
//    closesocket(connectionData.clientSocket);
//    WSACleanup();
//}
//
//int main() {
//    ConnectionData connectionData;
//    connectionData.getRequest = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
//
//    if (InitializeConnection(connectionData)) {
//        if (SendRequest(connectionData)) {
//            ReceiveAndDisplayResponse(connectionData);
//        }
//        CloseConnection(connectionData);
//    }
//
//    while (1) {
//    }
//
//    return 0;
//}
