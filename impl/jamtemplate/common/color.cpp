#include "color.hpp"

namespace jt {

bool operator==(jt::Color const& a, jt::Color const& b)
{
    return (a.r() == b.r() && a.g() == b.g() && a.b() == b.b() && a.a() == b.a());
}
bool operator!=(jt::Color const& a, jt::Color const& b) { return !(a == b); }

const jt::Color colors::Black { 0, 0, 0, 255 }; ///< Black predefined color
const jt::Color colors::White { 255, 255, 255, 255 }; ///< White predefined color
const jt::Color colors::Gray { 150, 150, 150, 255 }; ///< Gray predefined color
const jt::Color colors::Red { 255, 0, 0, 255 }; ///< Red predefined color
const jt::Color colors::Green { 0, 255, 0, 255 }; ///< Green predefined color
const jt::Color colors::Blue { 0, 0, 255, 255 }; ///< Blue predefined color
const jt::Color colors::Yellow { 255, 255, 0, 255 }; ///< Yellow predefined color
const jt::Color colors::Magenta { 255, 0, 255, 255 }; ///< Magenta predefined color
const jt::Color colors::Cyan { 0, 255, 255, 255 }; // namespace colors
const jt::Color colors::Transparent { 0, 0, 0, 0 }; ///< Transparent (black) predefined color

} // namespace jt
