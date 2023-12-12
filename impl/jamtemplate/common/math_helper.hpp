#ifndef JAMTEMPLATE_MATHHELPER_HPP
#define JAMTEMPLATE_MATHHELPER_HPP

#include <rect.hpp>
#include <vector.hpp>
#include <assert.h>
#include <bit>
#include <cmath>
#include <numbers>
#include <numeric>
#include <stdexcept>
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

#ifdef __clang__

// clang does not support std::bitcast yet
constexpr float qrsqrt(float x)
{
    if (x < 0) {
        throw std::invalid_argument { "argument of qrsqrt must be non-negative" };
    }
    return 1.0f / sqrt(x);
}

#else

constexpr float qrsqrt(float y)
{
    if (y < 0) {
        throw std::invalid_argument { "argument of qrsqrt must be non-negative" };
    }
    constexpr auto threeHalfes = 1.5f;
    auto const x2 = y * 0.5f;

    auto i = std::bit_cast<int>(y);
    i = 0x5f3759df - (i >> 1);
    y = std::bit_cast<float>(i);

    y = y * (threeHalfes - (x2 * y * y));
    return y;
}

#endif

constexpr float qsqrt(float y) { return y * qrsqrt(y); }

/// Calculate the squared length of a vector
///
/// This function is significantly faster than length, as it does not need to calculate the
/// squareroot
///
/// \param v vector to calculate squared length of \return squared length
constexpr float lengthSquared(jt::Vector2f const& v) noexcept { return v.x * v.x + v.y * v.y; }

/// Calculate the length of a vector (quick version that uses an approximation)
/// \param v vector to calculate length of
/// \return length (approximation, usually correct to ~ 0.1)
float qlength(jt::Vector2f const& v);

/// Calculate the length of a vector
/// \param v vector to calculate length of
/// \return length
float length(jt::Vector2f const& v);

/// CalculateDistanceBetween the two points
/// \param a position a
/// \param b position b
/// \return distance betwen a and b
float distanceBetween(jt::Vector2f const& a, jt::Vector2f const& b);

///  Squared Distance between
/// \param a position a
/// \param b position b
/// \return squared distance betwen a and b
float distanceBetweenSquared(jt::Vector2f const& a, jt::Vector2f const& b);

/// In-place normalize a vector
/// \param v vector to be normalized
/// \param lowerBound lower bound for the distance (to avoid divide by zero)
void normalizeMe(jt::Vector2f& v, float lowerBound = 0);

/// conversion from radiant to degree
/// \param alphaInRadiant angle in radiant
/// \return angle in degree
constexpr float rad2deg(float alphaInRadiant) noexcept
{
    constexpr auto half_circle = 180.0f;
    return static_cast<float>(alphaInRadiant * half_circle * std::numbers::inv_pi);
}

/// conversion from degree to radiant
/// \param alphaInDegree angle in degree
/// \return angle in radiant
constexpr float deg2rad(float alphaInDegree) noexcept
{
    constexpr auto half_circle = 180.0f;
    return static_cast<float>(alphaInDegree / half_circle * std::numbers::pi);
}

/// Rotate a vector by a given angle (counter-clockwise)
/// \param in input vector
/// \param aInDegree angle in degree
/// \return rotated output vector
jt::Vector2f rotateBy(jt::Vector2f const& in, float aInDegree) noexcept;

/// angle in degree between argument vector and the x axis
/// \param in input vector
/// \return angle in degree between in an x axis
constexpr float angleOf(jt::Vector2f const& in) noexcept
{
    return rad2deg(static_cast<float>(atan2(-in.y, in.x)));
}

/// specialization of clamp for a jt::Vector2f type
/// \param value the value
/// \param min minimal value
/// \param max maximal
/// \return the clamped value
template <typename T = jt::Vector2f>
jt::Vector2f clamp(
    jt::Vector2f const& value, jt::Vector2f const& min, jt::Vector2f const& max) noexcept
{
    assert(min.x < max.x);
    assert(min.y < max.y);

    auto v = value;

    if (value.x < min.x) {
        v.x = min.x;
    } else if (value.x > max.x) {
        v.x = max.x;
    }

    if (value.y < min.y) {
        v.y = min.y;
    } else if (value.y > max.y) {
        v.y = max.y;
    }

    return v;
}

/// Convert a floating point value to a string which contains a certain amount of decimal digits
/// \param number floating point number
/// \param number_of_decimal_digits number of decimal digits
/// \return string representation of the number
std::string floatToStringWithXDecimalDigits(
    float const number, unsigned int number_of_decimal_digits);

/// sign of a value
/// \tparam T
/// \param val
/// \return
template <typename T>
constexpr int sgn(T val) noexcept
{
    return (T(0) < val) - (val < T(0));
}

/// Check if a number is a power of two
/// \tparam T type (integer number)
/// \param v value
/// \return true if v is a power of two, false otherwise
template <typename T>
constexpr bool isPowerOfTwo(T v) noexcept
{
    return v && ((v & (v - 1)) == 0);
}

/// Dot product between two vectors
/// \param lhs first vector
/// \param rhs second vector
/// \return dot product between two vectors
constexpr float dot(Vector2f const& lhs, Vector2f const& rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

/// Check if a rect contains a point
/// \param rect rectangle
/// \param point point
/// \return true if point is in rect, false otherwise
constexpr bool checkIsIn(jt::Rectf const& rect, jt::Vector2f const& point) noexcept
{
    bool const overlapsX = point.x > rect.left && point.x < rect.left + rect.width;
    bool const overlapsY = point.y > rect.top && point.y < rect.top + rect.height;
    return (overlapsX && overlapsY);
}

/// Cast a jt::Vector2f to it's integer values. This is needed e.g. for drawing pixel-perfect.
/// \param input input vector
/// \return cast to integer position
constexpr jt::Vector2f castToInteger(jt::Vector2f const& input) noexcept
{
    return jt::Vector2f { static_cast<float>(static_cast<int>(input.x)),
        static_cast<float>(static_cast<int>(input.y)) };
}

} // namespace MathHelper
} // namespace jt

#endif
