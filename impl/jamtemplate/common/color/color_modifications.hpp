#ifndef GUARD_JAMTEMPLATE_COLOR_MODIFICATIONS_HPP
#define GUARD_JAMTEMPLATE_COLOR_MODIFICATIONS_HPP

#include "color/color.hpp"

namespace jt {
struct ColorModifications {
    /// Desaturate a color by a certain amount
    /// \param initialColor the initial color
    /// \param desaturationAmount the amount to decreate the saturation [0,100]
    /// \return the desaturated color
    static jt::Color desaturate(jt::Color const& initialColor, float desaturationAmount);
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_COLOR_MODIFICATIONS_HPP
