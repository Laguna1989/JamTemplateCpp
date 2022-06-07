#include "color_modifications.hpp"
#include <color/color_helpers.hpp>

jt::Color jt::ColorModifications::desaturate(
    jt::Color const& initialColor, float desaturationAmount)
{
    auto [h, s, v] = jt::ColorHelpers::rgb2hsv(initialColor.r, initialColor.g, initialColor.b);
    s -= desaturationAmount;
    if (s < 0) {
        s = 0;
    }
    auto const [r, g, b] = jt::ColorHelpers::hsv2rgb(h, s, v);
    return jt::Color { r, g, b, initialColor.a };
}

jt::Color jt::ColorModifications::saturate(jt::Color const& initialColor, float saturationAmount)
{
    auto [h, s, v] = jt::ColorHelpers::rgb2hsv(initialColor.r, initialColor.g, initialColor.b);
    s += saturationAmount;
    if (s > 100) {
        s = 100;
    }
    auto const [r, g, b] = jt::ColorHelpers::hsv2rgb(h, s, v);
    return jt::Color { r, g, b, initialColor.a };
}
