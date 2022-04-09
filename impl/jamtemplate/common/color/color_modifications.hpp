#ifndef GUARD_JAMTEMPLATE_COLOR_MODIFICATIONS_HPP
#define GUARD_JAMTEMPLATE_COLOR_MODIFICATIONS_HPP

#include "color/color.hpp"

namespace jt {
struct ColorModifications {
    static jt::Color desaturate(jt::Color const& initialColor, float desaturationAmount);
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_COLOR_MODIFICATIONS_HPP
