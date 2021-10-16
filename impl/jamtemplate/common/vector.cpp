#include "vector.hpp"

namespace jt {

jt::Vector2 operator+(jt::Vector2 const& a, jt::Vector2 const& b)
{
    return jt::Vector2 { a.x() + b.x(), a.y() + b.y() };
}

jt::Vector2 operator-(jt::Vector2 const& a, jt::Vector2 const& b)
{
    return jt::Vector2 { a.x() - b.x(), a.y() - b.y() };
}

bool operator==(jt::Vector2 const& a, jt::Vector2 const& b)
{
    return a.x() == b.x() && a.y() == b.y();
}

bool operator!=(jt::Vector2 const& a, jt::Vector2 const& b) { return !(a == b); }

jt::Vector2 operator*(float const f, jt::Vector2 const& v)
{
    return jt::Vector2 { f * v.x(), f * v.y() };
}
jt::Vector2 operator*(jt::Vector2 const& v, float const f) { return f * v; }

jt::Vector2 operator/(jt::Vector2 const& v, float const f)
{
    return jt::Vector2 { v.x() / f, v.y() / f };
}

jt::Vector2u operator+(jt::Vector2u const& a, jt::Vector2u const& b)
{
    return jt::Vector2u { a.x() + b.x(), a.y() + b.y() };
}
jt::Vector2u operator-(jt::Vector2u const& a, jt::Vector2u const& b)
{
    return jt::Vector2u { a.x() - b.x(), a.y() - b.y() };
}
bool operator==(jt::Vector2u const& a, jt::Vector2u const& b)
{
    return a.x() == b.x() && a.y() == b.y();
}
bool operator!=(jt::Vector2u const& a, jt::Vector2u const& b) { return !(a == b); }

} // namespace jt
