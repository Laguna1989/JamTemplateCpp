#include "sine.hpp"
#include <cmath>
#include <math.h>

namespace jt {
namespace ease {
namespace sine {

const float pi = 2.0f * static_cast<float>(std::acos(0.0f));

float easeIn(float t, float b, float c, float d) { return -c * cos(t / d * (pi / 2)) + c + b; }

float easeOut(float t, float b, float c, float d) { return c * sin(t / d * (pi / 2)) + b; }

float easeInOut(float t, float b, float c, float d) { return -c / 2 * (cos(pi * t / d) - 1) + b; }

} // namespace sine
} // namespace ease
} // namespace jt
