#include "color_modifications.hpp"
#include "color_helpers.hpp"

jt::Color jt::ColorModifications::desaturate(
    jt::Color const& initialColor, float desaturationAmount)
{
    auto hsvColor = jt::ColorHelpers::rgb2hsv(initialColor.r, initialColor.g, initialColor.b);
    std::get<1>(hsvColor) -= desaturationAmount;
    if (std::get<1>(hsvColor) < 0) {
        std::get<1>(hsvColor) = 0;
    }
    auto const rgb = jt::ColorHelpers::hsv2rgb(
        std::get<0>(hsvColor), std::get<1>(hsvColor), std::get<2>(hsvColor));
    return jt::Color { std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb), initialColor.a };
}
