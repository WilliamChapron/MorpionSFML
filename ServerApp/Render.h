#pragma once

#include <SFML/Graphics.hpp>

struct Render {
    sf::RenderWindow* pWindow;
    sf::Event* pEvent;
    int iWidth;
    int iHeight;
    void Update(); // D�placez la d�claration de la m�thode Update ici
};
