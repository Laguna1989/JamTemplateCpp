#include "color_modifications.hpp"
#include <color/color_helpers.hpp>
#include <cmath>

namespace {

template <typename T>
jt::Color conversionHelper(jt::Color const& initialColor, T const& innerFunc)
{
    auto const [h, s, v]
        = jt::ColorHelpers::rgb2hsv(initialColor.r, initialColor.g, initialColor.b);

    auto const [h2, s2, v2] = innerFunc(h, s, v);

    auto const [r, g, b] = jt::ColorHelpers::hsv2rgb(h2, s2, v2);
    return jt::Color { r, g, b, initialColor.a };
}
} // namespace

jt::Color jt::ColorModifications::desaturate(
    jt::Color const& initialColor, float desaturationAmount)
{
    return conversionHelper(initialColor, [&desaturationAmount](auto h, auto s, auto v) {
        s -= desaturationAmount;
        if (s < 0) {
            s = 0;
        }
        if (s > 100) {
            s = 100;
        }
        return std::make_tuple(h, s, v);
    });
}

jt::Color jt::ColorModifications::saturate(jt::Color const& initialColor, float saturationAmount)
{
    return desaturate(initialColor, -saturationAmount);
}

jt::Color jt::ColorModifications::rotateHue(jt::Color const& initialColor, float hueAngle)
{
    return conversionHelper(initialColor, [&hueAngle](auto h, auto s, auto v) {
        h += hueAngle;
        s = fmod(s, 360.0f);
        return std::make_tuple(h, s, v);
    });
}
