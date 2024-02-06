#include "GameManager.h"
#include <iostream>

GameManager::GameManager() : currentPlayer(nullptr) {
    player1 = new Player("William", Symbol::X, 1);
    player2 = new Player("Bot", Symbol::O, 2);
    currentPlayer = player1;
}

void GameManager::HandlePlayerAction(int cellIndex) {
    int placeState = morpion.placeSymbol(cellIndex);
    if (placeState == 0) {
        currentPlayer = (currentPlayer->symbol == Symbol::X) ? player2 : player1;
    }
}

std::string GameManager::GetGameState() {
    return morpion.getBoardState();
}
