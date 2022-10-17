#ifndef JAMTEMPLATE_COLOR_CONVERSIONS_HPP
#define JAMTEMPLATE_COLOR_CONVERSIONS_HPP

#include <color/color.hpp>
#include <cstdint>
#include <string>
#include <tuple>

namespace jt {
struct ColorConversions {

    /// Convert hsv to rgb
    /// \param h hue value [0-360]
    /// \param s saturation value [0-100]
    /// \param v value value [0-100]
    /// \return rgb tuple, each [0-255]
    static std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> hsv2rgb(float h, float s, float v);

    /// Convert rgb to hsv
    /// \param r red value [0-255]
    /// \param g green value [0-255]
    /// \param b blue value [0-255]
    /// \return hsv tuple [0-360], [0-100], [0-100]
    static std::tuple<float, float, float> rgb2hsv(std::uint8_t r, std::uint8_t g, std::uint8_t b);

    /// Convert hex string to rgb
    /// \param hexString starts with or without '#', two chars for r,g,b each in this order,
    /// ##FFFFFF \return rgb tuple, each [0-255]
    static std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> hex2rgb(
        std::string const& hexString);
};

} // namespace jt
#endif // JAMTEMPLATE_COLOR_CONVERSIONS_HPP
