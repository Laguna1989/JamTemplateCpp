#ifndef JAMTEMPLATE_CONVERSIONS_HPP_GUARD
#define JAMTEMPLATE_CONVERSIONS_HPP_GUARD

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace JamTemplate {

class C {
public:
    static sf::Vector2f vec(b2Vec2 v)
    {
        return sf::Vector2f { v.x, v.y };
    }

    static b2Vec2 vec(sf::Vector2f v)
    {
        return b2Vec2 { v.x, v.y };
    }
};
}

#endif // !JAMTEMPLATE_CONVERSIONS_HPP_GUARD
