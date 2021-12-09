#include "rect_lib.hpp"

sf::FloatRect jt::toLib(jt::Rectf const& rect)
{
    return sf::FloatRect { rect.left, rect.top, rect.width, rect.height };
}

jt::Rectf jt::fromLib(sf::Rect<float> rect)
{
    return jt::Rectf { rect.left, rect.top, rect.width, rect.height };
}

sf::IntRect jt::toLib(jt::Recti const& rect)
{
    return sf::IntRect { rect.left, rect.top, rect.width, rect.height };
}
jt::Recti jt::fromLib(sf::IntRect const& rect)
{
    return jt::Recti { rect.left, rect.top, rect.width, rect.height };
}
