#include "color_lib.hpp"

sf::Color jt::toLib(jt::Color const& col) { return sf::Color { col.r, col.g, col.b, col.a }; }
jt::Color jt::fromLib(sf::Color const& col) { return jt::Color { col.r, col.g, col.b, col.a }; }
