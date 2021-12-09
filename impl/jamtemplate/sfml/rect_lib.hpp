#ifndef GUARD_JAMTEMPLATE_RECT_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_RECT_LIB_GUARD_HPP

#include "rect.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace jt {

sf::FloatRect toLib(jt::Rectf const& rect);
jt::Rectf fromLib(sf::Rect<float> rect);

sf::IntRect toLib(jt::Recti const& rect);
jt::Recti fromLib(sf::IntRect const& rect);

} // namespace jt

#endif
