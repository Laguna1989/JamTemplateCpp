#ifndef GUARD_JAMTEMPLATE_CONVERSIONS_HPP_GUARD
#define GUARD_JAMTEMPLATE_CONVERSIONS_HPP_GUARD

#include "vector.hpp"
#include <Box2D/Box2D.h>
#include <tileson.h>

namespace jt {
namespace Conversion {

/// Convert box2d vector to jt vector
/// \param v the box2d vector
/// \return the jt vector
jt::Vector2f vec(b2Vec2 const& v);

/// Convert jt vector to box2d vector
/// \param v the jt vector
/// \return the box2d vector
b2Vec2 vec(jt::Vector2f const& v);

/// convert tson vector to jt vector
/// \param v the tson vector
/// \return the jt vector
jt::Vector2f vec(tson::Vector2f const& v);

/// convert jt vector to tson vector
/// \param v the jt vector
/// \return the tson vector
jt::Vector2f vec(tson::Vector2i const& v);

} // namespace Conversion
} // namespace jt

#endif // !JAMTEMPLATE_CONVERSIONS_HPP_GUARD
