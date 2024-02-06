#include "ServerSocket.h"
#include <iostream>

ServerSocket::ServerSocket(int port) : port(port), listenSocket(INVALID_SOCKET) {
}

ServerSocket::~ServerSocket() {
    Close();
}

bool ServerSocket::StartAsyncListening(HWND hwnd) {
    // Initialiser Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return false;
    }

    // Créer le socket
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return false;
    }

    // Configurer l'adresse du serveur
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) != 1) {
        std::cerr << "Failed to convert IP address." << std::endl;
        Close();
        return false;
    }

    serverAddress.sin_port = htons(port);

    // Lier le socket
    if (bind(listenSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket." << std::endl;
        Close();
        return false;
    }

    // Associer le socket à un événement
    if (WSAAsyncSelect(listenSocket, hwnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR) {
        std::cerr << "Failed to start asynchronous listening." << std::endl;
        Close();
        return false;
    }

    // Écouter les connexions entrantes
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen for incoming connections." << std::endl;
        Close();
        return false;
    }

    return true;
}

void ServerSocket::HandleClients() {
    // Cette fonction est destinée à être utilisée avec WSAAsyncSelect
    // Gérer les connexions et les données entrantes de manière asynchrone
    // Gérer les événements FD_ACCEPT et FD_READ dans la procédure de fenêtre

    // Vous devez implémenter la logique de cette fonction en fonction de vos besoins
    // par exemple, traiter les connexions entrantes, lire les données, etc.
}

void ServerSocket::BroadcastMessage(const std::string& message) {
    for (SOCKET clientSocket : clientSockets) {
        send(clientSocket, message.c_str(), message.size(), 0);
    }
}

void ServerSocket::Close() {
    for (SOCKET clientSocket : clientSockets) {
        closesocket(clientSocket);
    }
    WSACleanup();
}
