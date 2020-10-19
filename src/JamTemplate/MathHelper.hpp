#ifndef JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <vector>

namespace JamTemplate {

namespace MathHelper {

    // create a vector with numbers between a and b (both inclusive)
    // when called with vectorBetween(4,9) the resulting vector will be
    // [4, 5, 6, 7, 8, 9]
    template <typename T>
    inline std::vector<T> vectorBetween(T const& a, T const& b)
    {
        std::vector<T> values;
        for (T i = a; i != b + 1; ++i) {
            values.push_back(i);
        }
        return values;
    }

    inline float lengthSquared(sf::Vector2f const& v)
    {
        return v.x * v.x + v.y * v.y;
    }

    inline float length(sf::Vector2f const& v)
    {
        return std::sqrt(lengthSquared(v));
    }

    inline void normalizeMe(sf::Vector2f& v, float lowerbound = 0)
    {
        float l = length(v);
        if (l == 1) {
            return;
        }
        if (l > lowerbound) {
            v.x /= l;
            v.y /= l;
        }
    }

    inline float rad2deg(float a)
    {
        return a * 180.0f / 3.1415926f;
    }
    inline float deg2rad(float a)
    {
        return a / 180.0f * 3.1415926f;
    }

    template <typename T>
    inline T clamp(T const& value, T const& min, T const& max)
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
}

} // namespace JamTemplate

#endif
