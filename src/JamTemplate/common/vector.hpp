#ifndef VECTOR_GUARD_HPP_12345
#define VECTOR_GUARD_HPP_12345
#include "vector_base.hpp"

namespace jt {

jt::vector2 operator+(jt::vector2 const& a, jt::vector2 const& b);
jt::vector2 operator-(jt::vector2 const& a, jt::vector2 const& b);
bool operator==(jt::vector2 const& a, jt::vector2 const& b);
bool operator!=(jt::vector2 const& a, jt::vector2 const& b);

jt::vector2u operator+(jt::vector2u const& a, jt::vector2u const& b);
jt::vector2u operator-(jt::vector2u const& a, jt::vector2u const& b);
bool operator==(jt::vector2u const& a, jt::vector2u const& b);
bool operator!=(jt::vector2u const& a, jt::vector2u const& b);

} // namespace jt
#endif
