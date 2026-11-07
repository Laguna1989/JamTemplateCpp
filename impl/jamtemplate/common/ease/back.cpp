#include "back.hpp"

namespace jt {
namespace ease {
namespace back {

namespace {
constexpr float overshoot { 1.70158f };
constexpr float overshootInOut { overshoot * 1.525f };
} // namespace

float easeIn(float t, float b, float c, float d)
{
    float const p { t / d };
    return c * p * p * ((overshoot + 1.0f) * p - overshoot) + b;
}

float easeOut(float t, float b, float c, float d)
{
    float const q { t / d - 1.0f };
    return c * (q * q * ((overshoot + 1.0f) * q + overshoot) + 1.0f) + b;
}

float easeInOut(float t, float b, float c, float d)
{
    float const p { t / (d / 2.0f) };
    if (p < 1.0f) {
        return c / 2.0f * (p * p * ((overshootInOut + 1.0f) * p - overshootInOut)) + b;
    }
    float const q { p - 2.0f };
    return c / 2.0f * (q * q * ((overshootInOut + 1.0f) * q + overshootInOut) + 2.0f) + b;
}

} // namespace back
} // namespace ease
} // namespace jt
