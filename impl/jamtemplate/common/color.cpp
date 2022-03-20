#include "color.hpp"
#include "color_helpers.hpp"

bool jt::operator==(jt::Color const& a, jt::Color const& b)
{
    return (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}
bool jt::operator!=(jt::Color const& a, jt::Color const& b) { return !(a == b); }

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

    auto [r, g, b] = jt::ColorHelpers::hsv2rgb(h, s, v);
    return jt::Color { r, g, b, a };
}

jt::Color jt::MakeColor::FromHexString(std::string const& hexString)
{
    auto [r, g, b] = jt::ColorHelpers::hex2rgb(hexString);
    return jt::Color { r, g, b, 255 };
}

const jt::Color jt::colors::Black { 0, 0, 0, 255 }; ///< Black predefined color
const jt::Color jt::colors::White { 255, 255, 255, 255 }; ///< White predefined color
const jt::Color jt::colors::Gray { 150, 150, 150, 255 }; ///< Gray predefined color
const jt::Color jt::colors::Red { 255, 0, 0, 255 }; ///< Red predefined color
const jt::Color jt::colors::Green { 0, 255, 0, 255 }; ///< Green predefined color
const jt::Color jt::colors::Blue { 0, 0, 255, 255 }; ///< Blue predefined color
const jt::Color jt::colors::Yellow { 255, 255, 0, 255 }; ///< Yellow predefined color
const jt::Color jt::colors::Magenta { 255, 0, 255, 255 }; ///< Magenta predefined color
const jt::Color jt::colors::Cyan { 0, 255, 255, 255 }; ///< Cyan predefined color
const jt::Color jt::colors::Transparent { 0, 0, 0, 0 }; ///< Transparent (black) predefined color
