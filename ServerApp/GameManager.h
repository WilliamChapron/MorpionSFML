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

    void SetPlayers(Player* client1, Player* client2);
    void HandlePlayerAction(Player* player, Render render);
    std::string GetGameState();

    Player* player1;
    Player* player2;

private:
    Morpion morpion;
    Player* currentPlayer;

};

#endif
