#include "vector_lib.hpp"

sf::Vector2f jt::toLib(jt::Vector2f const& vec) { return sf::Vector2f { vec.x, vec.y }; }
jt::Vector2f jt::fromLib(sf::Vector2f const& vec) { return jt::Vector2f { vec.x, vec.y }; }

sf::Vector2u jt::toLib(jt::Vector2u const& vec) { return sf::Vector2u { vec.x, vec.y }; }
jt::Vector2u jt::fromLib(sf::Vector2u const& vec) { return jt::Vector2u { vec.x, vec.y }; }
