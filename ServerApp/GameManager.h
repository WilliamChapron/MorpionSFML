#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Morpion.h"
#include "Player.h"
#include "Render.h"
#include "ServerSocket.h"
#include "Defines.h"

class GameManager {
public:
    GameManager();

    void HandlePlayerAction(int cellIndex);
    std::string GetGameState();

private:
    Morpion morpion;
    Player* currentPlayer;
    Player* player1;
    Player* player2;
};

#endif
