#ifndef JAMTEMPLATE_MAKE_COLOR_HPP
#define JAMTEMPLATE_MAKE_COLOR_HPP

#include <color/color.hpp>

namespace jt {

/// Struct for accumulating color creation functionality
struct MakeColor {
    /// Create a color based on rgb values
    /// \param r red value [0-255]
    /// \param g green value [0-255]
    /// \param b blue value [0-255]
    /// \return the created Color object
    static jt::Color FromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b);

    /// Create a color based on rgba values
    /// \param r red value [0-255]
    /// \param g green value [0-255]
    /// \param b blue value [0-255]
    /// \param a alpha value [0-255]
    /// \return the created Color object
    static jt::Color FromRGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

    /// Create a color based on hsv values
    /// \param h hue value [0-360]
    /// \param s saturation value [0-100]
    /// \param v value value [0-100]
    /// \return the created Color object
    static jt::Color FromHSV(float h, float s, float v);

    /// Create a color based on hsva values
    /// \param h hue value [0-360]
    /// \param s saturation value [0-100]
    /// \param v value value [0-100]
    /// \param a alpha value [0-255]
    /// \return the created Color object
    static jt::Color FromHSVA(float h, float s, float v, std::uint8_t a);

    /// Create a color based on a hexstring
    /// \param hexString starts with or without '#', two chars for r,g,b each in this order
    /// \return the created Color object
    static jt::Color FromHexString(std::string const& hexString);
};

} // namespace jt

#endif // JAMTEMPLATE_MAKE_COLOR_HPP
