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

    // Constructeur priv� pour emp�cher l'instanciation directe
    App();
    ~App();
    static App* GetInstance();
    bool turn(sf::Vector2i mousePosition, int turnIndex, SOCKET inputSocket);

    void Init(HINSTANCE hInstance);
    void RunServerSocket();
    void RunServerWeb();

    // Acc�der � hwnd
    HWND GetHwnd() const { return hwnd; }

    // Acc�der � pServer
    ServerSocket* GetServerSocket() const { return pServer; }

    // Acc�der � pServerWeb
    ServerWeb* GetServerWeb() const { return pServerWeb; }

    // Acc�der � myMorpion
    Morpion* GetMorpion() const { return myMorpion; }

    // Acc�der � turnCounter
    int GetTurnCounter() const { return turnCounter; }

    // Acc�der � player1
    Player* GetPlayer1() const { return player1; }

    // Acc�der � player2
    Player* GetPlayer2() const { return player2; }

    // Acc�der � playerNumber
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

