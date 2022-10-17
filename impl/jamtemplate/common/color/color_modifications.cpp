#include "color_modifications.hpp"
#include "math_helper.hpp"
#include <color/color_conversions.hpp>
#include <cmath>

namespace {

template <typename T>
jt::Color conversionHelper(jt::Color const& initialColor, T const& innerFunc)
{
    auto const [h, s, v]
        = jt::ColorConversions::rgb2hsv(initialColor.r, initialColor.g, initialColor.b);

    auto const [h2, s2, v2] = innerFunc(h, s, v);

    auto const [r, g, b] = jt::ColorConversions::hsv2rgb(h2, s2, v2);
    return jt::Color { r, g, b, initialColor.a };
}
} // namespace

jt::Color jt::ColorModifications::desaturate(
    jt::Color const& initialColor, float desaturationAmount)
{
    return conversionHelper(initialColor, [&desaturationAmount](auto h, auto s, auto v) {
        s -= desaturationAmount;
        s = jt::MathHelper::clamp(s, 0.0f, 100.0f);
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
        h = fmod(h, 360.0f);
        return std::make_tuple(h, s, v);
    });
}

jt::Color jt::ColorModifications::darken(jt::Color const& initialColor, float value)
{
    return conversionHelper(initialColor, [&value](auto h, auto s, auto v) {
        v -= value;
        v = jt::MathHelper::clamp(v, 0.0f, 100.0f);
        return std::make_tuple(h, s, v);
    });
}

jt::Color jt::ColorModifications::lighten(jt::Color const& color, float value)
{
    return darken(color, -value);
}
