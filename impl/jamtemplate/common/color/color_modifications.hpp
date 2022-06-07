#ifndef JAMTEMPLATE_COLOR_MODIFICATIONS_HPP
#define JAMTEMPLATE_COLOR_MODIFICATIONS_HPP

#include <color/color.hpp>

namespace jt {
struct ColorModifications {
    /// Desaturate a color
    /// \param initialColor the initial color
    /// \param desaturationAmount the amount to decrease the saturation [0,100]
    /// \return the desaturated color
    static jt::Color desaturate(jt::Color const& initialColor, float desaturationAmount);

    /// Saturate a color
    /// \param initialColor the initial color
    /// \param saturationAmount the amount to increase the saturation [0,100]
    /// \return the saturated color
    static jt::Color saturate(jt::Color const& initialColor, float saturationAmount);

    /// Rotate hue of a color
    /// \param initialColor the initial color
    /// \param hueAngle the angle to rotate the hue [0,360]
    /// \return the color with the rotated hue
    static jt::Color rotateHue(jt::Color const& initialColor, float hueAngle);
};

} // namespace jt

#endif // JAMTEMPLATE_COLOR_MODIFICATIONS_HPP
