#include "vector.hpp"
#include <ostream>

jt::Vector2f::Vector2f(float x, float y)
    : x { x }
    , y { y }
{
}
jt::Vector2f::Vector2f()
    : x { 0.0f }
    , y { 0.0f }
{
}

jt::Vector2f jt::operator+(jt::Vector2f const& a, jt::Vector2f const& b)
{
    return jt::Vector2f { a.x + b.x, a.y + b.y };
}

jt::Vector2f jt::operator-(jt::Vector2f const& a, jt::Vector2f const& b)
{
    return jt::Vector2f { a.x - b.x, a.y - b.y };
}

jt::Vector2f& jt::operator+=(jt::Vector2f& lhs, jt::Vector2f const& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

jt::Vector2f& jt::operator-=(jt::Vector2f& lhs, jt::Vector2f const& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

bool jt::operator==(jt::Vector2f const& a, jt::Vector2f const& b)
{
    return a.x == b.x && a.y == b.y;
}

bool jt::operator!=(jt::Vector2f const& a, jt::Vector2f const& b) { return !(a == b); }

jt::Vector2f jt::operator*(float const f, jt::Vector2f const& v)
{
    return jt::Vector2f { f * v.x, f * v.y };
}
jt::Vector2f jt::operator*(jt::Vector2f const& v, float const f) { return f * v; }

jt::Vector2f jt::operator/(jt::Vector2f const& v, float const f)
{
    return jt::Vector2f { v.x / f, v.y / f };
}

std::ostream& jt::operator<<(std::ostream& os, jt::Vector2f const& vec)
{
    return os << "(" << vec.x << ", " << vec.y << ")";
}

jt::Vector2u::Vector2u(unsigned int x, unsigned int y)
    : x { x }
    , y { y }
{
}
jt::Vector2u::Vector2u()
    : x { 0U }
    , y { 0u }
{
}

jt::Vector2u jt::operator+(jt::Vector2u const& a, jt::Vector2u const& b)
{
    return jt::Vector2u { a.x + b.x, a.y + b.y };
}
jt::Vector2u jt::operator-(jt::Vector2u const& a, jt::Vector2u const& b)
{
    return jt::Vector2u { a.x - b.x, a.y - b.y };
}

jt::Vector2u& jt::operator+=(jt::Vector2u& lhs, jt::Vector2u const& other)
{
    lhs.x += other.x;
    lhs.y += other.y;
    return lhs;
}
jt::Vector2u& jt::operator-=(jt::Vector2u& lhs, jt::Vector2u const& other)
{
    lhs.x -= other.x;
    lhs.y -= other.y;
    return lhs;
}

bool jt::operator==(jt::Vector2u const& a, jt::Vector2u const& b)
{
    return a.x == b.x && a.y == b.y;
}
bool jt::operator!=(jt::Vector2u const& a, jt::Vector2u const& b) { return !(a == b); }

std::ostream& jt::operator<<(std::ostream& os, jt::Vector2u const& vec)
{
    return os << "(" << vec.x << ", " << vec.y << ")";
}
