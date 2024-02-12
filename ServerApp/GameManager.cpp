//#include "GameManager.h"
//#include <iostream>
//
//GameManager::GameManager() : currentPlayer(nullptr), player1(nullptr), player2(nullptr) {
//    // Ne pas initialiser les joueurs car ce seront les clients
//}
//
//void GameManager::SetPlayers(Player* client1, Player* client2) {
//    player1 = client1;
//    player2 = client2;
//    currentPlayer = player1;
//}
//
//void GameManager::HandlePlayerAction(Player* player, Render render) {
//    if (player == currentPlayer) {
//        int placeState = morpion.placeSymbol(render);
//        if (placeState == 0) {
//            currentPlayer = (currentPlayer == player1) ? player2 : player1; // switch joueur apr�s chaque coup
//            // Maintenant, vous pouvez envoyer les mises � jour de l'�tat du jeu aux clients ici
//        }
//    }
//}
//
//
//std::string GameManager::GetGameState() {
//    return morpion.getBoardState();
//}
//
