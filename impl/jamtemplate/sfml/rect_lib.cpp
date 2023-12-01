#include "rect_lib.hpp"

sf::FloatRect jt::toLib(jt::Rectf const& rect) noexcept
{
    return sf::FloatRect { rect.left, rect.top, rect.width, rect.height };
}

jt::Rectf jt::fromLib(sf::Rect<float> rect) noexcept
{
    return jt::Rectf { rect.left, rect.top, rect.width, rect.height };
}

sf::IntRect jt::toLib(jt::Recti const& rect) noexcept
{
    return sf::IntRect { rect.left, rect.top, rect.width, rect.height };
}

jt::Recti jt::fromLib(sf::IntRect const& rect) noexcept
{
    return jt::Recti { rect.left, rect.top, rect.width, rect.height };
}
