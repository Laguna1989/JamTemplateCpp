#include "expo.hpp"
#include <math.h>

namespace jt {
namespace ease {
namespace expo {
float easeIn(float t, float b, float c, float d)
{
    return static_cast<float>((t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b);
}

float easeOut(float t, float b, float c, float d)
{
    return static_cast<float>((t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b);
}

float easeInOut(float t, float b, float c, float d)
{
    if (t == 0)
        return b;
    if (t == d)
        return b + c;
    if ((t /= d / 2) < 1)
        return static_cast<float>(c / 2 * pow(2, 10 * (t - 1)) + b);
    return static_cast<float>(c / 2 * (-pow(2, -10 * --t) + 2) + b);
}

} // namespace expo
} // namespace ease
} // namespace jt
