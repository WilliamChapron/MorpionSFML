#pragma once

#include <SFML/Graphics.hpp>

struct Render {
    sf::RenderWindow* pWindow;
    sf::Event* pEvent;
    int iWidth;
    int iHeight;
    void Update(); // Déplacez la déclaration de la méthode Update ici
};
