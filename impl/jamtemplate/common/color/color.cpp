#include "color.hpp"
#include <ostream>

bool jt::operator==(jt::Color const& a, jt::Color const& b)
{
    return (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}
bool jt::operator!=(jt::Color const& a, jt::Color const& b) { return !(a == b); }

std::ostream& jt::operator<<(std::ostream& os, const jt::Color& color)
{
    os << "( " << static_cast<int>(color.r) << ", " << static_cast<int>(color.g) << ", "
       << static_cast<int>(color.b) << ", " << static_cast<int>(color.a) << " )";
    return os;
}

const jt::Color jt::colors::Black { 0, 0, 0, 255 }; ///< Black predefined color
const jt::Color jt::colors::White { 255, 255, 255, 255 }; ///< White predefined color
const jt::Color jt::colors::Gray { 150, 150, 150, 255 }; ///< Gray predefined color
const jt::Color jt::colors::Red { 255, 0, 0, 255 }; ///< Red predefined color
const jt::Color jt::colors::Green { 0, 255, 0, 255 }; ///< Green predefined color
const jt::Color jt::colors::Blue { 0, 0, 255, 255 }; ///< Blue predefined color
const jt::Color jt::colors::Yellow { 255, 255, 0, 255 }; ///< Yellow predefined color
const jt::Color jt::colors::Magenta { 255, 0, 255, 255 }; ///< Magenta predefined color
const jt::Color jt::colors::Cyan { 0, 255, 255, 255 }; ///< Cyan predefined color
const jt::Color jt::colors::Transparent { 0, 0, 0, 0 }; ///< Transparent (black) predefined color
