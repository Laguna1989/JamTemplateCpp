#include "MathHelper.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

namespace jt {
namespace MathHelper {

const float pi = 2.0f * std::acos(0.0f);

float lengthSquared(jt::Vector2 const& v) { return v.x() * v.x() + v.y() * v.y(); }

float length(jt::Vector2 const& v) { return std::sqrt(lengthSquared(v)); }

void normalizeMe(jt::Vector2& v, float lowerbound)
{
    float l = length(v);
    if (l == 1) {
        return;
    }
    if (l > lowerbound) {
        v.x() /= l;
        v.y() /= l;
    }
}

float rad2deg(float a) { return a * 180.0f / pi; }
float deg2rad(float a) { return a / 180.0f * pi; }

jt::Vector2 rotateBy(jt::Vector2 const& in, float aInDegree)
{
    float x = cos(deg2rad(aInDegree)) * in.x() - sin(deg2rad(aInDegree)) * in.y();
    float y = sin(deg2rad(aInDegree)) * in.x() + cos(deg2rad(aInDegree)) * in.y();

    return jt::Vector2 { x, y };
}

std::string floatToStringWithXDigits(float const number, unsigned int digits)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(digits) << number;
    return stream.str();
}

} // namespace MathHelper

} // namespace jt
