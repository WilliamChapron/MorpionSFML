
//#include <SFML/Graphics.hpp>
//#include "Render.h"
//#include "Input.h"
//#include "Morpion.h"
//#include "Player.h"
//#include "Defines.h"

//

#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "ServerSocket.h"
#include "Defines.h"


#include "Time.h"


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


int main(int argc, char** argv)
{

    std::cout << "SERVER" << std::endl;
    

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    ServerSocket server(80);
    if (server.StartListening()) {
        server.HandleClients();
    }

    return 0;






    ////Création d'une fenêtre
    //Render myRenderer{new sf::RenderWindow(sf::VideoMode(640, 480), "SFML"), new sf::Event, 640, 480};
    //Morpion* myMorpion;
    //myMorpion = new Morpion;

    //Player* player1 = nullptr;
    //player1 = new Player{ "William", Symbol::X, 0};

    //Player* player2 = nullptr;
    //player2 = new Player{ "Bot", Symbol::O, 0 };


    ////GameLoop
    //myMorpion->drawBoard(myRenderer);
    //myMorpion->currentPlayer = player1;
    //int turnCounter = 0;
    //while (myRenderer.pWindow->isOpen())
    //{

    //    


    //    //EVENT
    //    int inputState = updateInput(myRenderer);
    //    //PRINT(myMorpion.currentPlayer->name)
    //    if (inputState == 0) {
    //        //PRINT("Pas d'Input")
    //        continue;
    //    }
    //    else if(inputState == 1) {
    //        if (!turn(myRenderer, myMorpion, turnCounter))
    //        {
    //            continue;
    //        };
    //    }




   



    //    //PRINT("Action")

    //    //UPDATE

    //    //DRAW
    //    if (myMorpion->checkEnd(Symbol::X) || myMorpion->checkEnd(Symbol::O)) {
    //        PRINT("Partie terminé, joueur gagnant :")
    //        PRINT(myMorpion->currentPlayer->name);
    //        //break;
    //    }

    //    // Transition next it
    //    myMorpion->currentPlayer = (turnCounter % 2 == 0) ? player2 : player1;
    //    turnCounter++;


    //}

    return 0;
}

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
