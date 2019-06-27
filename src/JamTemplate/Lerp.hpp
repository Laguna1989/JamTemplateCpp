#ifndef JAMTEMPLATE_LERP_HPP_INCLUDEGUARD
#define JAMTEMPLATE_LERP_HPP_INCLUDEGUARD

#include <assert.h>

namespace JamTemplate {
class Lerp {
public:
    Lerp() = delete;

    // linear interpolation between a and b with t between 0 and 1
    template <typename T>
    static T linear(T const& a, T const& b, T const& ti)
    {
        auto t = precheck(ti);
        assert(t >= 0.0 && t <= 1.0);
        return (1.0f - t) * a + t * b;
    }

    template <typename T>
    static T cosine(T const& a, T const& b, T const& t)
    {
        assert(t >= 0 && t <= 1);
        float tRemapCosine = (1.0f - static_cast<float>(cos(t * 3.1415926f))) * 0.5f;
        return linear(a, b, tRemapCosine);
    }

    template <typename T>
    static T cubic(T const& a, T const& b, T const& t)
    {
        assert(t >= 0 && t <= 1);
        float cub = t * t * t;
        return linear(a, b, cub);
    }

    template <typename T>
    static T cubicInvers(T const& a, T const& b, T const& t)
    {
        assert(t >= 0 && t <= 1);
        float cub = (1 - t) * (1 - t) * (1 - t);
        return linear(a, b, cub);
    }

    template <typename T>
    static T bounce(T const& a, T const& b, T t)
    {
        assert(t >= 0 && t <= 1);
        if ((t) < (1 / 2.75f)) {
            return b * (7.5625f * t * t) + a;
        } else if (t < (2 / 2.75f)) {
            float postFix = t -= (1.5f / 2.75f);
            return b * (7.5625f * (postFix)*t + .75f) + a;
        } else if (t < (2.5 / 2.75)) {
            float postFix = t -= (2.25f / 2.75f);
            return b * (7.5625f * (postFix)*t + .9375f) + a;
        } else {
            float postFix = t -= (2.625f / 2.75f);
            return b * (7.5625f * (postFix)*t + .984375f) + a;
        }
    }

    template <typename T>
    static T bounceInvers(T const& a, T const& b, T& t)
    {
        return b - bounce(a, b, 1 - t) + a;
    }

private:
    template <typename T>
    static T precheck(T const& ti)
    {
        T t = ti;
        if (t < 0)
            t = 0;
        if (t > 1)
            t = 1;
        return t;
    }
};
}

#endif
