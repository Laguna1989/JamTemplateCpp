#ifndef JAMTEMPLATE_MATHHELPER_HPP
#define JAMTEMPLATE_MATHHELPER_HPP

#include <rect.hpp>
#include <vector.hpp>
#include <assert.h>
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
    std::vector<T> values;
    for (T i = a; i != b + 1; ++i) {
        values.push_back(i);
    }
    return values;
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

float dot(Vector2f const&, Vector2f const&);

bool checkIsIn(jt::Rectf const& r, jt::Vector2f const& p);

} // namespace MathHelper
} // namespace jt

#endif
