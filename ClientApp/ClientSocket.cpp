#include "ClientSocket.h"
#include "Defines.h"

ClientSocket::ClientSocket(const char* serverIp, int serverPort) 
{
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Création du socket client
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Configuration de l'adresse et du port du serveur
    serverAddress.sin_family = AF_INET;
    if (inet_pton(AF_INET, serverIp, &(serverAddress.sin_addr)) != 1) {
        std::cerr << "Erreur lors de la conversion de l'adresse IP." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
    }
    serverAddress.sin_port = htons(serverPort);
}

ClientSocket::~ClientSocket() 
{
    closesocket(clientSocket);
    WSACleanup();
}

bool ClientSocket::Connect() 
{
    PRINT("Connexion ... ");
    return connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) != SOCKET_ERROR;
}

bool ClientSocket::SendMessage(const char* message) 
{
    PRINT("Send message ... ");
    return send(clientSocket, message, strlen(message), 0) != SOCKET_ERROR;
}
