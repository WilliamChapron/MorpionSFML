
#pragma once

#include "Includes.h"
#include "ServerSocket.h"
#include "Morpion.h"
#include "Player.h"

class App {
private:
    HWND hwnd;
    ServerSocket* pServer;
    Morpion* myMorpion;
    int turnCounter;
    Player* player1;
    Player* player2;
    int playerNumber;

    FILE* pCout;

    // Instance statique de la classe
    static App* instance;

    // Constructeur privé pour empêcher l'instanciation directe
    App();

public:
    ~App();

    static App* GetInstance();

    void Init(HINSTANCE hInstance);
    void Run();
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
