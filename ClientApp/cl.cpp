#include <SFML/Graphics.hpp>
#include <iostream>
#include "ClientSocket.h"
#include "Defines.h"

int main() {
    // Création d'une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Tac Toe Client");

    // Créez une instance de ClientSocket pour communiquer avec le serveur
    ClientSocket client("127.0.0.1", 80);

    if (client.Connect()) {
        // Connectez-vous au serveur
        client.SendMessage("Connexion établie");

        // Boucle principale du client
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    // Récupérer les coordonnées de la souris
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    std::cout << "Coordonnées de la souris : " << mousePosition.x << ", " << mousePosition.y << std::endl;

                    // Envoyer les coordonnées de la souris au serveur
                    // Format : "X,Y"
                    std::string message = std::to_string(mousePosition.x) + "," + std::to_string(mousePosition.y);
                    client.SendMessage(message.c_str());
                }
            }

            window.clear();
            // Dessinez ici votre interface utilisateur, par exemple, une grille de tic-tac-toe
            window.display();
        }
    }

    return 0;
}
