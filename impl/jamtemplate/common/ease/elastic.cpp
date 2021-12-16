#include "elastic.hpp"
#include <cmath>
#include <math.h>

namespace jt {
namespace ease {
namespace elastic {

const float pi = 2.0f * static_cast<float>(std::acos(0.0f));

float easeIn(float t, float b, float c, float d)
{
    if (t == 0)
        return b;
    if ((t /= d) == 1)
        return b + c;
    float p = d * .3f;
    float a = c;
    float s = p / 4;
    float postFix = static_cast<float>(
        a * pow(2, 10 * (t -= 1))); // this is a fix, again, with post-increment operators
    return -(postFix * sin((t * d - s) * (2 * pi) / p)) + b;
}

float easeOut(float t, float b, float c, float d)
{
    if (t == 0)
        return b;
    if ((t /= d) == 1)
        return b + c;
    float p = d * .3f;
    float a = c;
    float s = p / 4;
    return static_cast<float>((a * pow(2, -10 * t) * sin((t * d - s) * (2 * pi) / p) + c + b));
}

float easeInOut(float t, float b, float c, float d)
{
    if (t == 0)
        return b;
    if ((t /= d / 2) == 2)
        return b + c;
    float p = d * (.3f * 1.5f);
    float a = c;
    float s = p / 4;

    if (t < 1) {
        float postFix = static_cast<float>(a * pow(2, 10 * (t -= 1))); // postIncrement is evil
        return -.5f * (postFix * sin((t * d - s) * (2 * pi) / p)) + b;
    }
    float postFix = static_cast<float>(a * pow(2, -10 * (t -= 1))); // postIncrement is evil
    return postFix * sin((t * d - s) * (2 * pi) / p) * .5f + c + b;
}

} // namespace elastic
} // namespace ease
} // namespace jt
