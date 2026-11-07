#include "quad.hpp"

namespace jt {
namespace ease {
namespace quad {

float easeIn(float t, float b, float c, float d)
{
    float const p { t / d };
    return c * p * p + b;
}

float easeOut(float t, float b, float c, float d)
{
    float const p { t / d };
    return -c * p * (p - 2.0f) + b;
}

float easeInOut(float t, float b, float c, float d)
{
    float const p { t / (d / 2.0f) };
    if (p < 1.0f) {
        return c / 2.0f * p * p + b;
    }
    float const q { p - 1.0f };
    return -c / 2.0f * (q * (q - 2.0f) - 1.0f) + b;
}

} // namespace quad
} // namespace ease
} // namespace jt
