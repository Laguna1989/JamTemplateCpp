#include "MathHelper.hpp"
#include <cmath>

namespace JamTemplate {
namespace MathHelper {

    float lengthSquared(sf::Vector2f const& v)
    {
        return v.x * v.x + v.y * v.y;
    }

    float length(sf::Vector2f const& v)
    {
        return std::sqrt(lengthSquared(v));
    }

    void normalizeMe(sf::Vector2f& v, float lowerbound)
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

    float rad2deg(float a)
    {
        return a * 180.0f / 3.1415926f;
    }
    float deg2rad(float a)
    {
        return a / 180.0f * 3.1415926f;
    }

}

} // namespace JamTemplate
