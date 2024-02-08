#include "ServerSocket.h"
#include <iostream>

ServerSocket::ServerSocket(int port) : port(port), listenSocket(INVALID_SOCKET) {
}

ServerSocket::~ServerSocket() {
    for (SOCKET clientSocket : clientSockets) {
        closesocket(clientSocket);
    }
    WSACleanup();
}

bool ServerSocket::StartAsyncListening(HWND* hwnd) {

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
        Close(listenSocket);
        return false;
    }

    serverAddress.sin_port = htons(port);

    // Lier le socket
    if (bind(listenSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket." << std::endl;
        Close(listenSocket);
        return false;
    }

    // Associer le socket à un événement
    if (WSAAsyncSelect(listenSocket, (*hwnd), WM_LISTEN_SOCKET, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR) {
        std::cerr << "Failed to start asynchronous listening." << std::endl;
        Close(listenSocket);
        return false;
    }

    // Écouter les connexions entrantes
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen for incoming connections." << std::endl;
        Close(listenSocket);
        return false;
    }

    return true;
}

void ServerSocket::AddClientSocket(SOCKET clientSocket, HWND* hwnd) {
    clientSockets.push_back(clientSocket);

    if (WSAAsyncSelect(clientSocket, (*hwnd), WM_CLIENTS_SOCKET, FD_READ | FD_CLOSE) == SOCKET_ERROR) {
        int errorCode = WSAGetLastError();
        std::cout << "Failed to start asynchronous listening for client socket. Error code: " << errorCode << std::endl;
    }
}



void ServerSocket::BroadcastMessage(const json& jsonData) {
    std::string jsonString = jsonData.dump(); // Json to string with nlohmann

    for (SOCKET clientSocket : clientSockets) {
        send(clientSocket, jsonString.c_str(), jsonString.size(), 0);
    }
}

void ServerSocket::Close(SOCKET clientSocket) {
    closesocket(clientSocket);
}
