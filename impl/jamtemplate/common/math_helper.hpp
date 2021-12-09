#ifndef GUARD_JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD

#include "vector.hpp"
#include <assert.h>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>
#include <string>
#include <utility>
#include <vector>

namespace jt {
namespace MathHelper {

/// Create a vector with numbers between a and b (both inclusive)
///
/// when called with numbersBetween(4,9) the resulting vector will be [4, 5, 6, 7, 8, 9]
///
/// \param a lower bound (inclusive)
/// \param b upper bound (inclusive)
/// \return vector with ints between a and b
template <typename T>
std::vector<T> numbersBetween(T a, T b)
{
    if (a > b) {
        std::swap(a, b);
    }
    auto const r = ranges::iota_view(a, b + 1);
    return std::vector<T>(r.begin(), r.end());
}

float lengthSquared(jt::Vector2f const& v);

float length(jt::Vector2f const& v);

void normalizeMe(jt::Vector2f& v, float lowerbound = 0);

float rad2deg(float a);
float deg2rad(float a);

jt::Vector2f rotateBy(jt::Vector2f const& in, float aInDegree);

// angle in degree between argument vector and the x axis
float angleOf(jt::Vector2f const& in);

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
