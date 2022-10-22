#include "color_factory.hpp"
#include <color/color_conversions.hpp>

jt::Color jt::ColorFactory::fromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    return jt::ColorFactory::fromRGBA(r, g, b, 255);
}

jt::Color jt::ColorFactory::fromRGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
    return jt::Color { r, g, b, a };
}

jt::Color jt::ColorFactory::fromHSV(float h, float s, float v)
{
    return jt::ColorFactory::fromHSVA(h, s, v, 255);
}

jt::Color jt::ColorFactory::fromHSVA(float h, float s, float v, std::uint8_t a)
{
    auto const [r, g, b] = jt::ColorConversions::hsv2rgb(h, s, v);
    return jt::Color { r, g, b, a };
}

jt::Color jt::ColorFactory::fromHexString(std::string const& hexString)
{
    auto [r, g, b] = jt::ColorConversions::hex2rgb(hexString);
    return jt::Color { r, g, b, 255 };
}
