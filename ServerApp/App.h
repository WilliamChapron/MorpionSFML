#pragma once

#include "Includes.h"

class ServerSocket;
class ServerWeb;
class Morpion;
class Player;



class App {
public:

    // Instance statique de la classe
    static App* instance;

    // Constructeur privé pour empêcher l'instanciation directe
    App();
    ~App();
    static App* GetInstance();
    bool turn(sf::Vector2i mousePosition, int turnIndex, SOCKET inputSocket);

    void Init(HINSTANCE hInstance);
    void RunServerSocket();
    void RunServerWeb();

    // Accéder à hwnd
    HWND GetHwnd() const { return hwnd; }

    // Accéder à pServer
    ServerSocket* GetServerSocket() const { return pServer; }

    // Accéder à pServerWeb
    ServerWeb* GetServerWeb() const { return pServerWeb; }

    // Accéder à myMorpion
    Morpion* GetMorpion() const { return myMorpion; }

    // Accéder à turnCounter
    int GetTurnCounter() const { return turnCounter; }

    // Accéder à player1
    Player* GetPlayer1() const { return player1; }

    // Accéder à player2
    Player* GetPlayer2() const { return player2; }

    // Accéder à playerNumber
    int GetPlayerNumber() const { return playerNumber; }

    // Setter pour player1
    void SetPlayer1(Player* newPlayer1) { player1 = newPlayer1; }

    // Setter pour player2
    void SetPlayer2(Player* newPlayer2) { player2 = newPlayer2; }

private:
    HWND hwnd;
    ServerSocket* pServer;
    ServerWeb* pServerWeb;
    Morpion* myMorpion;
    int turnCounter;
    Player* player1;
    Player* player2;
    int playerNumber;
};

