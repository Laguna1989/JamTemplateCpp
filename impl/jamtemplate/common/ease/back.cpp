#include "back.hpp"

namespace jt {
namespace ease {
namespace back {

float easeIn(float t, float b, float c, float d)
{
    float s = 1.70158f;
    float postFix = t /= d;
    return c * (postFix)*t * ((s + 1) * t - s) + b;
}

float easeOut(float t, float b, float c, float d)
{
    float s = 1.70158f;
    return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
}

float easeInOut(float t, float b, float c, float d)
{
    float s = 1.70158f;
    if ((t /= d / 2) < 1)
        return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;
    float postFix = t -= 2;
    return c / 2 * ((postFix)*t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
}

} // namespace back
} // namespace ease
} // namespace jt
