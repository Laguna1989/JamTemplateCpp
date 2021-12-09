#include "vector.hpp"

namespace jt {

jt::Vector2f operator+(jt::Vector2f const& a, jt::Vector2f const& b)
{
    return jt::Vector2f { a.x + b.x, a.y + b.y };
}

jt::Vector2f operator-(jt::Vector2f const& a, jt::Vector2f const& b)
{
    return jt::Vector2f { a.x - b.x, a.y - b.y };
}

jt::Vector2f& operator+=(Vector2f& lhs, Vector2f const& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

jt::Vector2f& operator-=(Vector2f& lhs, Vector2f const& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

bool operator==(jt::Vector2f const& a, jt::Vector2f const& b) { return a.x == b.x && a.y == b.y; }

bool operator!=(jt::Vector2f const& a, jt::Vector2f const& b) { return !(a == b); }

jt::Vector2f operator*(float const f, jt::Vector2f const& v)
{
    return jt::Vector2f { f * v.x, f * v.y };
}
jt::Vector2f operator*(jt::Vector2f const& v, float const f) { return f * v; }

jt::Vector2f operator/(jt::Vector2f const& v, float const f)
{
    return jt::Vector2f { v.x / f, v.y / f };
}

jt::Vector2u operator+(jt::Vector2u const& a, jt::Vector2u const& b)
{
    return jt::Vector2u { a.x + b.x, a.y + b.y };
}
jt::Vector2u operator-(jt::Vector2u const& a, jt::Vector2u const& b)
{
    return jt::Vector2u { a.x - b.x, a.y - b.y };
}

jt::Vector2u& operator+=(Vector2u& lhs, Vector2u const& other)
{
    lhs.x += other.x;
    lhs.y += other.y;
    return lhs;
}
jt::Vector2u& operator-=(Vector2u& lhs, Vector2u const& other)
{
    lhs.x -= other.x;
    lhs.y -= other.y;
    return lhs;
}

bool operator==(jt::Vector2u const& a, jt::Vector2u const& b) { return a.x == b.x && a.y == b.y; }
bool operator!=(jt::Vector2u const& a, jt::Vector2u const& b) { return !(a == b); }

} // namespace jt
