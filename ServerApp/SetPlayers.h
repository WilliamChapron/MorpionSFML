#pragma once
#ifndef SETPLAYERS_H
#define SETPLAYERS_H

#include "GameManager.h"

GameManager* g_gameManager;

void SetPlayersFromClients(Player* client1, Player* client2);

#endif
