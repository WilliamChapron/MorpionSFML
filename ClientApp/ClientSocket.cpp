#include "ClientSocket.h"
#include "Defines.h"
#include "Time.h"
#include "JSON.h"



ClientSocket::ClientSocket(const char* serverIp, int serverPort)
{
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Cr�ation du socket client
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Configuration de l'adresse et du port du serveur
    serverAddress.sin_family = AF_INET;
    if (inet_pton(AF_INET, serverIp, &(serverAddress.sin_addr)) != 1) {
        std::cerr << "Erreur lors de la conversion de l'adresse IP." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
    }
    serverAddress.sin_port = htons(serverPort);

    // Configuration du socket en mode non bloquant
    u_long mode = 1;
    ioctlsocket(clientSocket, FIONBIO, &mode);
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

bool ClientSocket::SendMessage(const json& jsonObject) {
    std::string message = jsonObject.dump();

    float startTime = getCurrentTime();

    if (send(clientSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR) {
        return false;
    }

    return true;
}



json ClientSocket::AwaitBroadcast() {
    json receivedJson = ReceiveJsonFromSocket(clientSocket);

    if (!receivedJson.empty()) {
        //std::cout << "Received from server: " << receivedJson.dump() << std::endl;
        return receivedJson;
    }
    return receivedJson;
}

void ClientSocket::Close()
{
    closesocket(clientSocket);
}

