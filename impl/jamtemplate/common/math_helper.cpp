#include "math_helper.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

constexpr double pi = 3.14159265358979323846;

float jt::MathHelper::lengthSquared(jt::Vector2f const& v) { return v.x * v.x + v.y * v.y; }

float jt::MathHelper::length(jt::Vector2f const& v)
{
    return std::sqrt(jt::MathHelper::lengthSquared(v));
}

void jt::MathHelper::normalizeMe(jt::Vector2f& v, float lowerbound)
{
    float l = jt::MathHelper::length(v);
    if (l == 1) {
        return;
    }
    if (l > lowerbound) {
        v.x /= l;
        v.y /= l;
    }
}

float jt::MathHelper::rad2deg(float a)
{
    auto const half_circle = 180.0f;
    return static_cast<float>(a * half_circle / pi);
}

float jt::MathHelper::deg2rad(float a)
{
    auto const half_circle = 180.0f;
    return static_cast<float>(a / half_circle * pi);
}

jt::Vector2f jt::MathHelper::rotateBy(jt::Vector2f const& in, float aInDegree)
{
    float const x = static_cast<float>(cos(deg2rad(aInDegree))) * in.x
        - static_cast<float>(sin(deg2rad(aInDegree))) * in.y;
    float const y = static_cast<float>(sin(deg2rad(aInDegree))) * in.x
        + static_cast<float>(cos(deg2rad(aInDegree))) * in.y;

    return jt::Vector2f { x, y };
}

std::string jt::MathHelper::floatToStringWithXDigits(float const number, unsigned int digits)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(static_cast<std::int64_t>(digits)) << number;
    return stream.str();
}

float jt::MathHelper::angleOf(jt::Vector2f const& in)
{
    return rad2deg(static_cast<float>(atan2(-in.y, in.x)));
}

float jt::MathHelper::dot(Vector2f const& lhs, Vector2f const& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

bool jt::MathHelper::checkIsIn(jt::Rectf const& r, jt::Vector2f const& p)
{
    bool const overlapsX = p.x > r.left && p.x < r.left + r.width;
    bool const overlapsY = p.y > r.top && p.y < r.top + r.height;
    return (overlapsX && overlapsY);
}
