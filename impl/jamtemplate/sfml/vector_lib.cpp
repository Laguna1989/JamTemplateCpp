#include "vector_lib.hpp"
namespace jt {
sf::Vector2f toLib(Vector2f const& vec) { return sf::Vector2f { vec.x, vec.y }; }
jt::Vector2f fromLib(sf::Vector2f const& vec) { return jt::Vector2f { vec.x, vec.y }; }

sf::Vector2u toLib(Vector2u const& vec) { return sf::Vector2u { vec.x, vec.y }; }
jt::Vector2u fromLib(sf::Vector2u const& vec) { return jt::Vector2u { vec.x, vec.y }; }

} // namespace jt
