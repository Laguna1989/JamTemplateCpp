#ifndef JAMTEMPLATE_PALETTE_HPP
#define JAMTEMPLATE_PALETTE_HPP

#include <color/color.hpp>
#include <cstddef>
#include <vector>

namespace jt {

/// Palette class to group colors together
class Palette {
public:
    /// Create an empty palette.
    Palette() = default;

    /// Create a palette from a list of colors.
    /// \param colors the colors in the palette.
    explicit Palette(std::vector<jt::Color> const& colors);

    /// Create a palette from a gradient with varying hue.
    /// \param hmin minimum hue value
    /// \param hmax maximum hue value
    /// \param s saturation
    /// \param v value
    /// \param steps how many colors should be in the palette
    /// \return the Palette object
    static Palette createGradientH(float hmin, float hmax, float s, float v, std::size_t steps);

    /// Create a palette from a gradient with varying saturation.
    /// \param h hue
    /// \param smin minimum saturation value
    /// \param smax maximum saturation value
    /// \param v value
    /// \param steps how many colors should be in the palette
    /// \return the palette object
    static Palette createGradientS(float h, float smin, float smax, float v, std::size_t steps);

    /// Create a palette from a gradient with varying value
    /// \param h hue
    /// \param s saturation
    /// \param vmin minimum value
    /// \param vmax maximum value
    /// \param steps how many colors should be in the palette
    /// \return the palette object
    static Palette createGradientV(float h, float s, float vmin, float vmax, std::size_t steps);

    /// Get the number of colors in the palette.
    /// \return the number of colors
    std::size_t size() const;

    /// Check if the palette contains any colors.
    /// \return true if empty, falso otherwise
    bool empty() const;

    /// Add a new color to the palette. Note: The palette is not modified, but a new Palette is
    /// returned.
    /// \param col The color to be added.
    /// \return the palette object
    [[nodiscard]] Palette addColor(jt::Color col) const;

    /// Get a color from the palette. Will raise an exception if index is out of bounds.
    /// \param idx the index of the color
    /// \return the Color
    jt::Color const& getColor(std::size_t idx) const;

    /// Parse a palette from a GPL string
    /// \param gplFileContent the content of the GPL file
    /// \return the palette object
    static Palette parseGPL(std::string const& gplFileContent);

    /// Parse a palette from a GPL file
    /// \param fileName the file to be parsed
    /// \return the palette object
    static Palette parseGPLFromFile(std::string const& fileName);

private:
    std::vector<jt::Color> m_colors;
};

} // namespace jt

#endif // JAMTEMPLATE_PALETTE_HPP
