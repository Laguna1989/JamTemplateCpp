#ifndef RECT_INCLUDEGUARD
#define RECT_INCLUDEGUARD

#include <SFML/Graphics.hpp>

struct Rect {
    sf::Vector2f position;
    sf::Vector2f sizeDiagonal;
    float rotation;
    std::string m_type;
};

#endif
