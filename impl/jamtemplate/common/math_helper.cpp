#include "math_helper.hpp"
#include <cstdint>
#include <iomanip>
#include <sstream>

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

jt::Vector2f jt::MathHelper::rotateBy(jt::Vector2f const& in, float aInDegree) noexcept
{
    float const x = static_cast<float>(cos(deg2rad(aInDegree))) * in.x
        - static_cast<float>(sin(deg2rad(aInDegree))) * in.y;
    float const y = static_cast<float>(sin(deg2rad(aInDegree))) * in.x
        + static_cast<float>(cos(deg2rad(aInDegree))) * in.y;

    return jt::Vector2f { x, y };
}

std::string jt::MathHelper::floatToStringWithXDecimalDigits(
    float const number, unsigned int number_of_decimal_digits)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(static_cast<std::int64_t>(number_of_decimal_digits))
           << number;
    return stream.str();
}
