#include "ClientWeb.h"
#include "Defines.h"
#include "Time.h"
#include "JSON.h"



ClientWeb::ClientWeb(const char* serverIp, int serverPort)
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

ClientWeb::~ClientWeb()
{
    closesocket(clientSocket);
    WSACleanup();
}

bool ClientWeb::Connect()
{
    PRINT("Connexion ... ");
    return connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) != SOCKET_ERROR;
}

bool ClientWeb::SendMessageWithResponse(const json& jsonObject) {
    std::string message = jsonObject.dump();

    float startTime = getCurrentTime();

    if (send(clientSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR) {
        return false;
    }

    return true;

    // * Return Response *

    char buffer[4024];
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
    }
}


json ClientSocket::AwaitBroadcast() {
    json receivedJson = ReceiveJsonFromSocket(clientSocket);

    if (!receivedJson.empty()) {
        //std::cout << "Received from server: " << receivedJson.dump() << std::endl;
        return receivedJson;
    }
    return receivedJson;
}

void ClientWeb::Close()
{
    closesocket(clientSocket);
}

