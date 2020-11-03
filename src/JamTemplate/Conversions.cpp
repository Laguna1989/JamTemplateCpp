#include "Conversions.hpp"

namespace JamTemplate {
namespace C {

sf::Vector2f vec(b2Vec2 const& v) { return sf::Vector2f { v.x, v.y }; }

b2Vec2 vec(sf::Vector2f const& v) { return b2Vec2 { v.x, v.y }; }

sf::Vector2f vec(tson::Vector2f const& v) { return sf::Vector2f { v.x, v.y }; }

} // namespace C
} // namespace JamTemplate
