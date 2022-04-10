#include "make_color.hpp"
#include <color/color_helpers.hpp>

jt::Color jt::MakeColor::FromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    return jt::MakeColor::FromRGBA(r, g, b, 255);
}

jt::Color jt::MakeColor::FromRGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
    return jt::Color { r, g, b, a };
}

jt::Color jt::MakeColor::FromHSV(float h, float s, float v)
{
    return jt::MakeColor::FromHSVA(h, s, v, 255);
}

jt::Color jt::MakeColor::FromHSVA(float h, float s, float v, std::uint8_t a)
{
    auto const [r, g, b] = jt::ColorHelpers::hsv2rgb(h, s, v);
    return jt::Color { r, g, b, a };
}

jt::Color jt::MakeColor::FromHexString(std::string const& hexString)
{
    auto [r, g, b] = jt::ColorHelpers::hex2rgb(hexString);
    return jt::Color { r, g, b, 255 };
}
