#include "linear.hpp"

namespace jt {
namespace ease {
namespace linear {

float easeNone(float t, float b, float c, float d) { return c * t / d + b; }
float easeIn(float t, float b, float c, float d) { return c * t / d + b; }
float easeOut(float t, float b, float c, float d) { return c * t / d + b; }
float easeInOut(float t, float b, float c, float d) { return c * t / d + b; }

} // namespace linear
} // namespace ease
} // namespace jt
