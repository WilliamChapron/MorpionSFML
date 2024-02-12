#pragma once

#include <iostream>
#include <array>

// Forward Declaration

namespace sf {
    class RenderWindow;
    class Event;
}

// Utils 


enum class Symbol {
    Empty,
    X,
    O
};




struct Render {
    sf::RenderWindow* pWindow;
    sf::Event* pEvent;
    int iWidth;
    int iHeight;
};

