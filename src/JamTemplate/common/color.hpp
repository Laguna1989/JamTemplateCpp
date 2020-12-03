#ifndef GUARD_JAMTEMPLATE_COLOR_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_COLOR_GUARD_HPP_12345

#include "color_lib.hpp"

namespace jt {

bool operator==(jt::color const& a, jt::color const& b);
bool operator!=(jt::color const& a, jt::color const& b);

struct colors {
    static const jt::color Black; ///< Black predefined color
    static const jt::color White; ///< White predefined color
    static const jt::color Red; ///< Red predefined color
    static const jt::color Green; ///< Green predefined color
    static const jt::color Blue; ///< Blue predefined color
    static const jt::color Yellow; ///< Yellow predefined color
    static const jt::color Magenta; ///< Magenta predefined color
    static const jt::color Cyan; ///< Cyan predefined color
    static const jt::color Transparent; ///< Transparent (black) predefined color
};

} // namespace jt

#endif
