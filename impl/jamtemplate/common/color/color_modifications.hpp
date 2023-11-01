#ifndef JAMTEMPLATE_COLOR_MODIFICATIONS_HPP
#define JAMTEMPLATE_COLOR_MODIFICATIONS_HPP

#include <color/color.hpp>

namespace jt {
struct ColorModifications {
    /// Desaturate a color
    /// \param initialColor initial color
    /// \param desaturationAmount amount to decrease the saturation [0,100]
    /// \return desaturated color
    static jt::Color desaturate(jt::Color const& initialColor, float desaturationAmount);

    /// Saturate a color
    /// \param initialColor initial color
    /// \param saturationAmount amount to increase the saturation [0,100]
    /// \return saturated color
    static jt::Color saturate(jt::Color const& initialColor, float saturationAmount);

    /// Rotate hue of a color
    /// \param initialColor initial color
    /// \param hueAngle angle to rotate the hue [0,360]
    /// \return color with the rotated hue
    static jt::Color rotateHue(jt::Color const& initialColor, float hueAngle);

    /// Darken a color
    /// \param initialColor initial color
    /// \param value value to darken the color [0,100]
    /// \return color with the darkened value
    static jt::Color darken(jt::Color const& initialColor, float value);

    /// Lighten a color
    /// \param initialColor initial color
    /// \param value value to lighten the color [0,100]
    /// \return color with the lightened value
    static jt::Color lighten(jt::Color const& color, float value);

    /// Complement of a color
    /// \param color initial color
    /// \return complement of the initial color
    static jt::Color complement(jt::Color const& color);
};

} // namespace jt

#endif // JAMTEMPLATE_COLOR_MODIFICATIONS_HPP
