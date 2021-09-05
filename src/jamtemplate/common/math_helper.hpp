#ifndef GUARD_JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD

#include "vector.hpp"
#include <assert.h>
#include <string>
#include <utility>
#include <vector>

namespace jt {
namespace MathHelper {

// create a vector with numbers between a and b (both inclusive)
// when called with vectorBetween(4,9) the resulting vector will be
// [4, 5, 6, 7, 8, 9]
template <typename T>
std::vector<T> vectorBetween(T a, T b)
{
    if (a > b) {
        std::swap(a, b);
    }
    std::vector<T> values;
    for (T i = a; i != b + 1; ++i) {
        values.push_back(i);
    }
    return values;
}

float lengthSquared(jt::Vector2 const& v);

float length(jt::Vector2 const& v);

void normalizeMe(jt::Vector2& v, float lowerbound = 0);

float rad2deg(float a);
float deg2rad(float a);

jt::Vector2 rotateBy(jt::Vector2 const& in, float aInDegree);

// angle in degree between argument vector and the x axis
float angleOf(jt::Vector2 const& in);

template <typename T>
T clamp(T const& value, T const& min, T const& max)
{
    assert(min < max);
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

std::string floatToStringWithXDigits(float const number, unsigned int digits);

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
constexpr bool is_powerof2(T v)
{
    return v && ((v & (v - 1)) == 0);
}

} // namespace MathHelper
} // namespace jt

#endif
