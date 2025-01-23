#include "vector.hpp"
#include <ostream>

jt::Vector2f& jt::operator+=(jt::Vector2f& lhs, jt::Vector2f const& rhs) noexcept
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

jt::Vector2f& jt::operator-=(jt::Vector2f& lhs, jt::Vector2f const& rhs) noexcept
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

jt::Vector2f& jt::operator*=(jt::Vector2f& lhs, float const& rhs) noexcept
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}

std::ostream& jt::operator<<(std::ostream& os, jt::Vector2f const& vec)
{
    return os << "(" << vec.x << ", " << vec.y << ")";
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

std::ostream& jt::operator<<(std::ostream& os, jt::Vector2u const& vec)
{
    return os << "(" << vec.x << ", " << vec.y << ")";
}
