
//#include "Includes.h"
//#include <iostream>
//#include "Defines.h"
//#include "Render.h"
//#include "Input.h"
//
//
//int updateInput(Render render) {
//    if (render.pWindow->pollEvent(*(render.pEvent))) {
//        if (render.pEvent->type == sf::Event::Closed) {
//            PRINT("CLOSE");
//            render.pWindow->close();
//        }
//        if (render.pEvent->type == sf::Event::MouseButtonPressed && render.pEvent->mouseButton.button == sf::Mouse::Left) {
//            PRINT("left click");
//            return 1;
//        }
//    }
//    return 0;
//}
//
//sf::Vector2i getMousePosition(Render render) {
//    sf::Vector2i currentPosition = sf::Mouse::getPosition((*(render.pWindow)));
//    return currentPosition;
//}