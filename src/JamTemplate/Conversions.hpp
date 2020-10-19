#ifndef JAMTEMPLATE_CONVERSIONS_HPP_GUARD
#define JAMTEMPLATE_CONVERSIONS_HPP_GUARD

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace JamTemplate {

namespace C {
    inline sf::Vector2f vec(b2Vec2 const& v)
    {
        return sf::Vector2f { v.x, v.y };
    }

    inline b2Vec2 vec(sf::Vector2f const& v)
    {
        return b2Vec2 { v.x, v.y };
    }
}

}

#endif // !JAMTEMPLATE_CONVERSIONS_HPP_GUARD
