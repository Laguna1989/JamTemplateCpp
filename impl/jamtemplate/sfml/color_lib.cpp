#include "color_lib.hpp"

namespace jt {

sf::Color toLib(jt::Color const& col) { return sf::Color { col.r, col.g, col.b, col.a }; }
jt::Color fromLib(sf::Color const& col) { return jt::Color { col.r, col.g, col.b, col.a }; }

} // namespace jt
