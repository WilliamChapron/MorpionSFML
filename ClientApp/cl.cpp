#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "ClientSocket.h"
#include "Defines.h"

#include "Time.h"
#include <chrono>
#include <thread>



int main() {
    // Première connexion
    ClientSocket client("127.0.0.1", 80);
    client.Connect();

    // Attendre un peu
    std::this_thread::sleep_for(std::chrono::seconds(2));
    ClientSocket clientt("127.0.0.1", 80);
    clientt.Connect();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    ClientSocket clienttt("127.0.0.1", 80);
    clienttt.Connect();


    std::this_thread::sleep_for(std::chrono::seconds(2));
    printTimestamp();
    std::cout << "CLIENT 3" << std::endl;
    clienttt.SendMessage("CLIENT 3");

    std::this_thread::sleep_for(std::chrono::seconds(2));
    printTimestamp();
    std::cout << "CLIENT 2" << std::endl;
    clientt.SendMessage("CLIENT 2");

    std::this_thread::sleep_for(std::chrono::seconds(2));
    printTimestamp();
    std::cout << "CLIENT 1" << std::endl;
    client.SendMessage("CLIENT 1");



    return 0;
}