#include "circ.hpp"
#include <math.h>

namespace jt {
namespace ease {
namespace circ {

float easeIn(float t, float b, float c, float d)
{
    return -c * static_cast<float>(sqrt(1 - (t /= d) * t) - 1) + b;
}
float easeOut(float t, float b, float c, float d)
{
    return c * static_cast<float>(sqrt(1 - (t = t / d - 1) * t)) + b;
}

float easeInOut(float t, float b, float c, float d)
{
    if ((t /= d / 2) < 1) {
        return -c / 2 * static_cast<float>(sqrt(1 - t * t) - 1) + b;
    }
    return c / 2 * static_cast<float>(sqrt(1 - t * (t -= 2)) + 1) + b;
}

} // namespace circ
} // namespace ease
} // namespace jt
