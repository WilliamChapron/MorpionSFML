#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "ClientSocket.h"


int main() {
    //// Initialize WSA variables
    //std::cout << "CLIENT" << std::endl;
    //WSADATA wsaData;
    //int wsaerr;
    //WORD wVersionRequested = MAKEWORD(2, 2);
    //WSAStartup(wVersionRequested, &wsaData);

    //// Création du socket client
    //SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //// Configuration de l'adresse et du port du serveur
    //sockaddr_in serverAddress;
    //serverAddress.sin_family = AF_INET;
    //if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) != 1) {
    //    std::cerr << "Erreur lors de la conversion de l'adresse IP." << std::endl;
    //    closesocket(clientSocket);
    //    WSACleanup();
    //    return 1;
    //}
    //serverAddress.sin_port = htons(55555);

    //// Connexion au serveur
    //connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));

    //// Envoyer un message au serveur
    //const char* message = "Hello, Server!";
    //send(clientSocket, message, strlen(message), 0);

    ClientSocket client("127.0.0.1", 55555); // Remplacez l'adresse IP par celle de votre serveur
    if (client.Connect()) {
        client.SendMessage("Hello, Server!");
    }



    while (1);


    return 0;
}
