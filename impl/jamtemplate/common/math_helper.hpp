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

/// Calculate the squared length of a vector
///
/// This function is significantly faster than length, as it does not need to calculate the
/// squareroot \param v vector to calculate squared length of \return squared length
float lengthSquared(jt::Vector2f const& v);

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
/// \param aInRadiant angle in radiant
/// \return angle in degree
float rad2deg(float aInRadiant);

/// conversion from degree to radiant
/// \param aInDegree angle in degree
/// \return angle in radiant
float deg2rad(float aInDegree);

/// Rotate a vector by a given angle (counter-clockwise)
/// \param in input vector
/// \param aInDegree angle in degree
/// \return rotated output vector
jt::Vector2f rotateBy(jt::Vector2f const& in, float aInDegree);

/// angle in degree between argument vector and the x axis
/// \param in input vector
/// \return angle in degree between in an x axis
float angleOf(jt::Vector2f const& in);

/// clamp a value to a range [min, max]
/// \tparam T type
/// \param value the value
/// \param min minimal value
/// \param max maximal
/// \return the clamped value
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

/// specialization of clamp for a jt::Vector2f type
/// \param value the value
/// \param min minimal value
/// \param max maximal
/// \return the clamped value
template <typename T = jt::Vector2f>
jt::Vector2f clamp(jt::Vector2f const& value, jt::Vector2f const& min, jt::Vector2f const& max)
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
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

/// Check if a number is a power of two
/// \tparam T type (integer number)
/// \param v value
/// \return true if v is a power of two, false otherwise
template <typename T>
constexpr bool isPowerOfTwo(T v)
{
    return v && ((v & (v - 1)) == 0);
}

/// Dot product between two vectors
/// \param a first vector
/// \param b second vector
/// \return dot product between two vectors
float dot(Vector2f const& a, Vector2f const& b);

/// Check if a rect contains a point
/// \param rect rectangle
/// \param point point
/// \return true if point is in rect, false otherwise
bool checkIsIn(jt::Rectf const& rect, jt::Vector2f const& point);

/// Cast a jt::Vector2f to it's integer values. This is needed e.g. for drawing pixel-perfect.
/// \param input input vector
/// \return cast to integer position
jt::Vector2f castToInteger(jt::Vector2f const& input);

} // namespace MathHelper
} // namespace jt

#endif
