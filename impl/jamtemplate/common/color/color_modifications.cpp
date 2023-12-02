#include "color_modifications.hpp"
#include "math_helper.hpp"
#include <color/color_conversions.hpp>
#include <cmath>
#include <algorithm>
#include <concepts>

namespace {

jt::Color conversionHelper(
    jt::Color const& initialColor, std::invocable<float, float, float> auto const& innerFunc)
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
        s = std::clamp(s, 0.0f, 100.0f);
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
        v = std::clamp(v, 0.0f, 100.0f);
        return std::make_tuple(h, s, v);
    });
}

jt::Color jt::ColorModifications::lighten(jt::Color const& color, float value)
{
    return darken(color, -value);
}

jt::Color jt::ColorModifications::complement(jt::Color const& color)
{
    return jt::Color {
        // clang-format off
        static_cast<std::uint8_t>(255u - color.r),
        static_cast<std::uint8_t>(255u - color.g),
        static_cast<std::uint8_t>(255u - color.b),
        color.a
        // clang-format on
    };
}
