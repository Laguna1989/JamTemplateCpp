﻿#include "MathHelper.hpp"
#include <cmath>

namespace jt {
namespace MathHelper {

float lengthSquared(jt::vector2 const& v) { return v.x() * v.x() + v.y() * v.y(); }

float length(jt::vector2 const& v) { return std::sqrt(lengthSquared(v)); }

void normalizeMe(jt::vector2& v, float lowerbound)
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

float rad2deg(float a) { return a * 180.0f / 3.1415926f; }
float deg2rad(float a) { return a / 180.0f * 3.1415926f; }

std::string floatToStringWithXDigits(float const number, unsigned int digits)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(digits) << number;
    return stream.str();
}

} // namespace MathHelper

} // namespace jt
