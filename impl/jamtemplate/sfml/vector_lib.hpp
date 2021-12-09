#ifndef GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP

#include "vector.hpp"
#include <SFML/System/Vector2.hpp>

namespace jt {

sf::Vector2f toLib(jt::Vector2f const& vec);
jt::Vector2f fromLib(sf::Vector2f const& vec);

sf::Vector2u toLib(jt::Vector2u const& vec);
jt::Vector2u fromLib(sf::Vector2u const& vec);

} // namespace jt

#endif
