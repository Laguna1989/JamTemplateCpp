#ifndef JAMTEMPLATE_COLOR_HPP
#define JAMTEMPLATE_COLOR_HPP

#include <iosfwd>
#include <string>

namespace jt {

struct Color {
    std::uint8_t r { 0 };
    std::uint8_t g { 0 };
    std::uint8_t b { 0 };
    std::uint8_t a { 255 };
};

bool operator==(jt::Color const& a, jt::Color const& b);
bool operator!=(jt::Color const& a, jt::Color const& b);

std::ostream& operator<<(std::ostream& os, const jt::Color& color);

struct colors {
    static const jt::Color Black; ///< Black predefined color
    static const jt::Color White; ///< White predefined color
    static const jt::Color Gray; ///< Gray predefined color
    static const jt::Color Red; ///< Red predefined color
    static const jt::Color Green; ///< Green predefined color
    static const jt::Color Blue; ///< Blue predefined color
    static const jt::Color Yellow; ///< Yellow predefined color
    static const jt::Color Magenta; ///< Magenta predefined color
    static const jt::Color Cyan; ///< Cyan predefined color
    static const jt::Color Transparent; ///< Transparent (black) predefined color
};

} // namespace jt

#endif
