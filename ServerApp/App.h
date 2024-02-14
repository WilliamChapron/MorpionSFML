#pragma once

#include "Includes.h"

class ServerSocket;
class ServerWeb;
class Morpion;
class Player;



class App {
private:


    // Instance statique de la classe
    static App* instance;

    // Constructeur privé pour empêcher l'instanciation directe
    App();

public:

    HWND hwnd;
    ServerSocket* pServer;
    ServerWeb* pServerWeb;
    Morpion* myMorpion;
    int turnCounter;
    Player* player1;
    Player* player2;
    int playerNumber;

    ~App();

    static App* GetInstance();
    bool turn(sf::Vector2i mousePosition, int turnIndex, SOCKET inputSocket);

    void Init(HINSTANCE hInstance);
    static void RunServerSocket();
    static void RunServerWeb();
};

