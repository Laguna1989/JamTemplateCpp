#include "vector.hpp"

namespace jt {

jt::vector2 operator+(jt::vector2 const& a, jt::vector2 const& b)
{
    return jt::vector2 { a.x() + b.x(), a.y() + b.y() };
}

jt::vector2 operator-(jt::vector2 const& a, jt::vector2 const& b)
{
    return jt::vector2 { a.x() - b.x(), a.y() - b.y() };
}

bool operator==(jt::vector2 const& a, jt::vector2 const& b)
{
    return a.x() == b.x() && a.y() == b.y();
}

bool operator!=(jt::vector2 const& a, jt::vector2 const& b) { return !(a == b); }

jt::vector2u operator+(jt::vector2u const& a, jt::vector2u const& b)
{
    return jt::vector2u { a.x() + b.x(), a.y() + b.y() };
}
jt::vector2u operator-(jt::vector2u const& a, jt::vector2u const& b)
{
    return jt::vector2u { a.x() - b.x(), a.y() - b.y() };
}
bool operator==(jt::vector2u const& a, jt::vector2u const& b)
{
    return a.x() == b.x() && a.y() == b.y();
}
bool operator!=(jt::vector2u const& a, jt::vector2u const& b) { return !(a == b); }

} // namespace jt
