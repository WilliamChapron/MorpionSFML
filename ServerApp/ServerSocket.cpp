#include "ServerSocket.h"
#include "Defines.h"

ServerSocket::ServerSocket(int port) : port(port), listenSocket(INVALID_SOCKET) 
{
}

ServerSocket::~ServerSocket() {
    Close();
}

bool ServerSocket::StartListening() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return false;
    }

    // Create socket
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return false;
    }

    // Configure server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Bind the socket
    if (bind(listenSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket." << std::endl;
        Close();
        return false;
    }

    return true;
}

SOCKET ServerSocket::AcceptConnection() {
    // Listen for incoming connections
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen for incoming connections." << std::endl;
        Close();
        return INVALID_SOCKET;
    }

    // Accept the connection
    SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to accept connection." << std::endl;
        Close();
        return INVALID_SOCKET;
    }

    return clientSocket;
}

void ServerSocket::HandleClients() {
    while (true) {
        SOCKET clientSocket = AcceptConnection();
        if (clientSocket != INVALID_SOCKET) {
            // Add the new client socket to the vector
            clientSockets.push_back(clientSocket);

            PRINT("handle client");
            BroadcastMessage("Le serveur a une mise à jour!");

            while (true) {
                char buffer[4096];
                int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    std::cout << "Received from client: " << buffer << std::endl;


                    if (std::string(buffer) == "exit") {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            closesocket(clientSocket);
        }
    }
}

void ServerSocket::BroadcastMessage(const std::string& message) {
    for (SOCKET clientSocket : clientSockets) {
        send(clientSocket, message.c_str(), message.size(), 0);
        // Vous devrez gérer la logique d'erreur, la déconnexion éventuelle, etc.
    }
}

void ServerSocket::Close() {
    for (SOCKET clientSocket : clientSockets) {
        closesocket(clientSocket);
    }
    WSACleanup();
}
