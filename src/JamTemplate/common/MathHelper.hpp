#ifndef JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace JamTemplate {
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

float lengthSquared(sf::Vector2f const& v);

float length(sf::Vector2f const& v);

void normalizeMe(sf::Vector2f& v, float lowerbound = 0);

float rad2deg(float a);
float deg2rad(float a);

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

} // namespace MathHelper
} // namespace JamTemplate

#endif
