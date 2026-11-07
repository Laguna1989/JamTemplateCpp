#pragma once

#include <color/color.hpp>
#include <SFML/Graphics/Color.hpp>

namespace jt {

sf::Color toLib(jt::Color const& col) noexcept;
jt::Color fromLib(sf::Color const& col) noexcept;

} // namespace jt
