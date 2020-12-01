#ifndef VECTOR_GUARD_HPP_12345
#define VECTOR_GUARD_HPP_12345

/*
Note: vector_base.hpp should provide a class vector2
It needs to provide functions with the following signatures:

    float x() const
    float y() const

    float& x()
    float& y()

a class vector2u needs to provide functions with the following signatures:
    unsigned int x() const
    unsigned int y() const

    unsigned int& x()
    unsigned int& y()

the functions in this file will only use the functions mentioned above.
To avoid instantiation of vectors as pointer-like-objects, it was decided
to not have a common base class.
*/
#include "vector_base.hpp"

namespace jt {

jt::vector2 operator+(jt::vector2 const& a, jt::vector2 const& b);
jt::vector2 operator-(jt::vector2 const& a, jt::vector2 const& b);
bool operator==(jt::vector2 const& a, jt::vector2 const& b);
bool operator!=(jt::vector2 const& a, jt::vector2 const& b);

jt::vector2 operator*(float const f, jt::vector2 const& v);
jt::vector2 operator*(jt::vector2 const& v, float const f);

jt::vector2u operator+(jt::vector2u const& a, jt::vector2u const& b);
jt::vector2u operator-(jt::vector2u const& a, jt::vector2u const& b);
bool operator==(jt::vector2u const& a, jt::vector2u const& b);
bool operator!=(jt::vector2u const& a, jt::vector2u const& b);

} // namespace jt
#endif
