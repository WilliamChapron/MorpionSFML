#pragma once

#include "Includes.h"

class ServerSocket;
class ServerWeb;
class Morpion;
class Player;



class App {
public:
    static App* instance;

    App();
    ~App();
    static App* GetInstance();
    bool turn(sf::Vector2i mousePosition, int turnIndex, SOCKET inputSocket);

    void Init(HINSTANCE hInstance);
    void RunServerSocket();
    void RunServerWeb();

    HWND GetHwnd() const { return hwnd; }
    ServerSocket* GetServerSocket() const { return pServer; }
    ServerWeb* GetServerWeb() const { return pServerWeb; }
    Morpion* GetMorpion() const { return myMorpion; }
    int GetTurnCounter() const { return turnCounter; }
    Player* GetPlayer1() const { return player1; }
    Player* GetPlayer2() const { return player2; }
    int GetPlayerNumber() const { return playerNumber; }
    void SetPlayer1(Player* newPlayer1) { player1 = newPlayer1; }
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

