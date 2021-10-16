#ifndef GUARD_JAMTEMPLATE_VECTOR_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_VECTOR_GUARD_HPP_12345

#include "vector_lib.hpp"

namespace jt {

jt::Vector2 operator+(jt::Vector2 const& a, jt::Vector2 const& b);
jt::Vector2 operator-(jt::Vector2 const& a, jt::Vector2 const& b);
bool operator==(jt::Vector2 const& a, jt::Vector2 const& b);
bool operator!=(jt::Vector2 const& a, jt::Vector2 const& b);

jt::Vector2 operator*(float const f, jt::Vector2 const& v);
jt::Vector2 operator*(jt::Vector2 const& v, float const f);

jt::Vector2 operator/(jt::Vector2 const& v, float const f);

jt::Vector2u operator+(jt::Vector2u const& a, jt::Vector2u const& b);
jt::Vector2u operator-(jt::Vector2u const& a, jt::Vector2u const& b);
bool operator==(jt::Vector2u const& a, jt::Vector2u const& b);
bool operator!=(jt::Vector2u const& a, jt::Vector2u const& b);

} // namespace jt

#endif
