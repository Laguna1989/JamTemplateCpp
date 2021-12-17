#include "quad.hpp"

namespace jt {
namespace ease {
namespace quad {

float easeIn(float t, float b, float c, float d) { return c * (t /= d) * t + b; }

float easeOut(float t, float b, float c, float d) { return -c * (t /= d) * (t - 2) + b; }

float easeInOut(float t, float b, float c, float d)
{
    if ((t /= d / 2) < 1)
        return ((c / 2) * (t * t)) + b;
    return -c / 2 * (((t - 2) * (--t)) - 1) + b;
    /*
    originally return -c/2 * (((t-2)*(--t)) - 1) + b;

    I've had to swap (--t)*(t-2) due to diffence in behaviour in
    pre-increment operators between java and c++, after hours
    of joy
    */
}
} // namespace quad
} // namespace ease
} // namespace jt
