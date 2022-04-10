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
