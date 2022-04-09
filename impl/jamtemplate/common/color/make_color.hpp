#ifndef GUARD_JAMTEMPLATE_MAKE_COLOR_HPP
#define GUARD_JAMTEMPLATE_MAKE_COLOR_HPP

#include "color.hpp"

namespace jt {

struct MakeColor {
    static jt::Color FromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b);
    static jt::Color FromRGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
    static jt::Color FromHSV(float h, float s, float v);
    static jt::Color FromHSVA(float h, float s, float v, std::uint8_t a);
    static jt::Color FromHexString(std::string const& hexString);
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_MAKE_COLOR_HPP
