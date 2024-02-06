#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include "ServerSocket.h"
#include "GameManager.h" // Importer la classe GameManager
#include "Defines.h"

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Créer une instance de GameManager
    GameManager gameManager;

    // Initialiser le serveur de sockets
    ServerSocket server(80);

    if (server.StartListening()) {
        // Boucle principale du serveur
        while (true) {
            server.HandleClients(gameManager); // Gérer les connexions des clients en passant le GameManager
        }
    }

    WSACleanup();

    return 0;
}