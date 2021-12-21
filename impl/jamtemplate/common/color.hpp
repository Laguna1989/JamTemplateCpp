#ifndef GUARD_JAMTEMPLATE_COLOR_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_COLOR_GUARD_HPP_12345

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

namespace MakeColor {

jt::Color FromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b);
jt::Color FromRGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

jt::Color FromHSV(float h, float s, float v);
jt::Color FromHSVA(float h, float s, float v, std::uint8_t a);

jt::Color FromHexString(std::string const& hexString);

} // namespace MakeColor

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
