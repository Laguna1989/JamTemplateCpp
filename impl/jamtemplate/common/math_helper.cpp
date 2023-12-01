#include "math_helper.hpp"

#include <iomanip>
#include <sstream>

float jt::MathHelper::lengthSquared(jt::Vector2f const& v) { return v.x * v.x + v.y * v.y; }

float jt::MathHelper::qlength(jt::Vector2f const& v)
{
    return jt::MathHelper::qsqrt(jt::MathHelper::lengthSquared(v));
}

float jt::MathHelper::length(jt::Vector2f const& v)
{
    return std::sqrt(jt::MathHelper::lengthSquared(v));
}

float jt::MathHelper::distanceBetween(jt::Vector2f const& a, jt::Vector2f const& b)
{
    auto const dir = b - a;
    return length(dir);
}

float jt::MathHelper::distanceBetweenSquared(jt::Vector2f const& a, jt::Vector2f const& b)
{
    auto const dir = b - a;
    return lengthSquared(dir);
}

void jt::MathHelper::normalizeMe(jt::Vector2f& v, float lowerBound)
{
    float l = jt::MathHelper::length(v);
    if (l == 1) {
        return;
    }
    if (l > lowerBound) {
        v.x /= l;
        v.y /= l;
    }
}

std::string jt::MathHelper::floatToStringWithXDecimalDigits(
    float const number, unsigned int number_of_decimal_digits)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(static_cast<std::int64_t>(number_of_decimal_digits))
           << number;
    return stream.str();
}

float jt::MathHelper::angleOf(jt::Vector2f const& in) noexcept
{
    return rad2deg(static_cast<float>(atan2(-in.y, in.x)));
}

float jt::MathHelper::dot(Vector2f const& lhs, Vector2f const& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

bool jt::MathHelper::checkIsIn(jt::Rectf const& rect, jt::Vector2f const& point)
{
    bool const overlapsX = point.x > rect.left && point.x < rect.left + rect.width;
    bool const overlapsY = point.y > rect.top && point.y < rect.top + rect.height;
    return (overlapsX && overlapsY);
}

jt::Vector2f jt::MathHelper::castToInteger(jt::Vector2f const& input)
{
    return jt::Vector2f { static_cast<float>(static_cast<int>(input.x)),
        static_cast<float>(static_cast<int>(input.y)) };
}
