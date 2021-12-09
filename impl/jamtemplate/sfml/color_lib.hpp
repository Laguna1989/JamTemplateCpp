#ifndef GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP

#include "color.hpp"
#include <SFML/Graphics/Color.hpp>

namespace jt {

sf::Color toLib(jt::Color const& col);
jt::Color fromLib(sf::Color const& col);

} // namespace jt

#endif
