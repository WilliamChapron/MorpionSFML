#include "Render.h"

void Render::Update() {
    sf::Event event;
    while (pWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            pWindow->close();
        }
    }
}
