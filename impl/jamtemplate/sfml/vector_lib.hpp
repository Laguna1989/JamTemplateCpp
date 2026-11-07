#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector.hpp>

namespace jt {

sf::Vector2f toLib(jt::Vector2f const& vec) noexcept;
jt::Vector2f fromLib(sf::Vector2f const& vec) noexcept;

sf::Vector2u toLib(jt::Vector2u const& vec) noexcept;
jt::Vector2u fromLib(sf::Vector2u const& vec) noexcept;

} // namespace jt
