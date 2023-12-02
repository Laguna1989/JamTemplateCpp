#include "math_helper.hpp"

#include <iomanip>
#include <sstream>

float jt::MathHelper::qlength(jt::Vector2f const& v)
{
    return jt::MathHelper::qsqrt(jt::MathHelper::lengthSquared(v));
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
