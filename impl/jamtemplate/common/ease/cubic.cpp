#include "cubic.hpp"

namespace jt {
namespace ease {
namespace cubic {

float easeIn(float t, float b, float c, float d)
{
    float const p { t / d };
    return c * p * p * p + b;
}

float easeOut(float t, float b, float c, float d)
{
    float const q { t / d - 1.0f };
    return c * (q * q * q + 1.0f) + b;
}

float easeInOut(float t, float b, float c, float d)
{
    float const p { t / (d / 2.0f) };
    if (p < 1.0f) {
        return c / 2.0f * p * p * p + b;
    }
    float const q { p - 2.0f };
    return c / 2.0f * (q * q * q + 2.0f) + b;
}

} // namespace cubic
} // namespace ease
} // namespace jt
