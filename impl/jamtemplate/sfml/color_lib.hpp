#pragma once

#include <SFML/Graphics/Color.hpp>
#include <color/color.hpp>

namespace jt {

sf::Color toLib(jt::Color const& col) noexcept;
jt::Color fromLib(sf::Color const& col) noexcept;

} // namespace jt
