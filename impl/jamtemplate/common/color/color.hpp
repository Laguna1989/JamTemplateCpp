#ifndef JAMTEMPLATE_COLOR_HPP
#define JAMTEMPLATE_COLOR_HPP

#include <cstdint>
#include <iosfwd>
#include <string>

namespace jt {

struct Color {
    std::uint8_t r { 0 };
    std::uint8_t g { 0 };
    std::uint8_t b { 0 };
    std::uint8_t a { 255 };
};

constexpr bool operator==(jt::Color const& a, jt::Color const& b) noexcept
{
    return (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}

constexpr bool operator!=(jt::Color const& a, jt::Color const& b) noexcept { return !(a == b); };

std::ostream& operator<<(std::ostream& os, jt::Color const& color);

namespace colors {

constexpr inline jt::Color Black { 0, 0, 0, 255 }; ///< Black predefined color
constexpr inline jt::Color White { 255, 255, 255, 255 }; ///< White predefined color
constexpr inline jt::Color Gray { 150, 150, 150, 255 }; ///< Gray predefined color
constexpr inline jt::Color Red { 255, 0, 0, 255 }; ///< Red predefined color
constexpr inline jt::Color Green { 0, 255, 0, 255 }; ///< Green predefined color
constexpr inline jt::Color Blue { 0, 0, 255, 255 }; ///< Blue predefined color
constexpr inline jt::Color Yellow { 255, 255, 0, 255 }; ///< Yellow predefined color
constexpr inline jt::Color Magenta { 255, 0, 255, 255 }; ///< Magenta predefined color
constexpr inline jt::Color Cyan { 0, 255, 255, 255 }; ///< Cyan predefined color
constexpr inline jt::Color Transparent { 0, 0, 0, 0 }; ///< Transparent (black) predefined color

} // namespace colors

} // namespace jt

#endif
