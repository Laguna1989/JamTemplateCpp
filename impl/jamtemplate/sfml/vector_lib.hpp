#ifndef JAMTEMPLATE_VECTOR_LIB_HPP
#define JAMTEMPLATE_VECTOR_LIB_HPP

#include <vector.hpp>
#include <SFML/System/Vector2.hpp>

namespace jt {

sf::Vector2f toLib(jt::Vector2f const& vec) noexcept;
jt::Vector2f fromLib(sf::Vector2f const& vec) noexcept;

sf::Vector2u toLib(jt::Vector2u const& vec) noexcept;
jt::Vector2u fromLib(sf::Vector2u const& vec) noexcept;

} // namespace jt

#endif
