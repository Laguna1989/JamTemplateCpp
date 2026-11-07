#include "circ.hpp"
#include <cmath>

namespace jt {
namespace ease {
namespace circ {

float easeIn(float t, float b, float c, float d)
{
    float const p { t / d };
    return -c * (std::sqrt(1.0f - p * p) - 1.0f) + b;
}

float easeOut(float t, float b, float c, float d)
{
    float const q { t / d - 1.0f };
    return c * std::sqrt(1.0f - q * q) + b;
}

float easeInOut(float t, float b, float c, float d)
{
    float const p { t / (d / 2.0f) };
    if (p < 1.0f) {
        return -c / 2.0f * (std::sqrt(1.0f - p * p) - 1.0f) + b;
    }
    float const q { p - 2.0f };
    return c / 2.0f * (std::sqrt(1.0f - q * q) + 1.0f) + b;
}

} // namespace circ
} // namespace ease
} // namespace jt
