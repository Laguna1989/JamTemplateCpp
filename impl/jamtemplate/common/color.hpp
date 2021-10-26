#ifndef GUARD_JAMTEMPLATE_COLOR_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_COLOR_GUARD_HPP_12345

#include "color_lib.hpp"

namespace jt {

bool operator==(jt::Color const& a, jt::Color const& b);
bool operator!=(jt::Color const& a, jt::Color const& b);

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
