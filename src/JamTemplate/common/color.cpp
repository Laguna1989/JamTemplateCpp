#include "color.hpp"

namespace jt {

bool operator==(jt::color const& a, jt::color const& b)
{
    return (a.r() == b.r() && a.g() == b.g() && a.b() == b.b() && a.a() == b.a());
}
bool operator!=(jt::color const& a, jt::color const& b) { return !(a == b); }

const jt::color colors::Black { 0, 0, 0, 255 }; ///< Black predefined color
const jt::color colors::White { 255, 255, 255, 255 }; ///< White predefined color
const jt::color colors::Red { 255, 0, 0, 255 }; ///< Red predefined color
const jt::color colors::Green { 0, 255, 0, 255 }; ///< Green predefined color
const jt::color colors::Blue { 0, 0, 255, 255 }; ///< Blue predefined color
const jt::color colors::Yellow { 255, 255, 0, 255 }; ///< Yellow predefined color
const jt::color colors::Magenta { 255, 0, 255, 255 }; ///< Magenta predefined color
const jt::color colors::Cyan { 0, 255, 255, 255 }; // namespace colors
const jt::color colors::Transparent { 0, 0, 0, 0 }; ///< Transparent (black) predefined color

} // namespace jt
