#include "ClientSocket.h"
#include "Defines.h"
#include "Time.h"


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

bool ClientSocket::SendMessage(const char* message) {
    PRINT("Send message ... ");

    float startTime = getCurrentTime();

    if (send(clientSocket, message, strlen(message), 0) == SOCKET_ERROR) {
        return false;
    }

    return true;

    /*char buffer[4024];
    int bytesRead;

    while (true) {
        if (getCurrentTime() > startTime + 10) {
            std::cout << "Err_Connection_Timed_Out :" << std::endl;
            return false;
        }

        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            std::string receivedData(buffer, bytesRead);
            std::cout << "Received from server: " << receivedData << std::endl;
            return true;
        }
    }*/
}

void ClientSocket::AwaitBroadcast() {
    char buffer[4024];
    int bytesRead;

    while (true) {
        PRINT("Attente")
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        PRINT(bytesRead)
        if (bytesRead >= 0) {
            PRINT("Pas de lecture")
            return;
        }
        if (bytesRead > 0) {
            PRINT("Une lecture")
            std::string receivedData(buffer, bytesRead);
            std::cout << "Received from server: " << receivedData << std::endl;
        }
        
    }
}

void ClientSocket::Close()
{
    closesocket(clientSocket);
}

