#include "color_builder.hpp"
#include <color/color_conversions.hpp>

jt::Color jt::ColorBuilder::fromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    return jt::ColorBuilder::fromRGBA(r, g, b, 255);
}

jt::Color jt::ColorBuilder::fromRGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
    return jt::Color { r, g, b, a };
}

jt::Color jt::ColorBuilder::fromHSV(float h, float s, float v)
{
    return jt::ColorBuilder::fromHSVA(h, s, v, 255);
}

jt::Color jt::ColorBuilder::fromHSVA(float h, float s, float v, std::uint8_t a)
{
    auto const [r, g, b] = jt::ColorConversions::hsv2rgb(h, s, v);
    return jt::Color { r, g, b, a };
}

jt::Color jt::ColorBuilder::fromHexString(std::string const& hexString)
{
    auto [r, g, b] = jt::ColorConversions::hex2rgb(hexString);
    return jt::Color { r, g, b, 255 };
}
