#ifndef JAMTEMPLATE_COLOR_LIB_HPP
#define JAMTEMPLATE_COLOR_LIB_HPP

#include <color/color.hpp>
#include <SFML/Graphics/Color.hpp>

namespace jt {

sf::Color toLib(jt::Color const& col);
jt::Color fromLib(sf::Color const& col);

} // namespace jt

#endif
