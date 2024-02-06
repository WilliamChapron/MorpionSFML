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
    ClientSocket client("127.0.0.1", 80);
    
    if (client.Connect()) {
        client.SendMessage("Premier message");
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    client.SendMessage("Deuxième message");



    return 0;
}