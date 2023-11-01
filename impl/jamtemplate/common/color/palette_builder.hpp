
#ifndef JAMTEMPLATE_PALETTE_BUILDER_HPP
#define JAMTEMPLATE_PALETTE_BUILDER_HPP

#include <color/palette.hpp>
#include <sprite.hpp>

namespace jt {

class PaletteBuilder {
public:
    /// Convert the PaletteBuilder into a Palette
    /// \return the palette object
    [[nodiscard]] Palette create() const;

    /// Parse a palette from a GPL string
    /// \param gplFileContent the content of the GPL file
    /// \return the palette builder object (fluent interface)
    [[nodiscard]] PaletteBuilder& addColorsFromGPL(std::string const& gplFileContent);

    /// Create a palette from a gradient with varying hue.
    /// \param hmin minimum hue value
    /// \param hmax maximum hue value
    /// \param s saturation
    /// \param v value
    /// \param steps how many colors should be in the palette
    /// \return the palette builder object (fluent interface)
    [[nodiscard]] PaletteBuilder& addGradientH(
        float hmin, float hmax, float s, float v, std::size_t steps);

    /// Create a palette from a gradient with varying saturation.
    /// \param h hue
    /// \param smin minimum saturation value
    /// \param smax maximum saturation value
    /// \param v value
    /// \param steps how many colors should be in the palette
    /// \return the palette builder object (fluent interface)
    [[nodiscard]] PaletteBuilder& addGradientS(
        float h, float smin, float smax, float v, std::size_t steps);

    /// Create a palette from a gradient with varying value
    /// \param h hue
    /// \param s saturation
    /// \param vmin minimum value
    /// \param vmax maximum value
    /// \param steps how many colors should be in the palette
    /// \return the palette builder object (fluent interface)
    [[nodiscard]] PaletteBuilder& addGradientV(
        float h, float s, float vmin, float vmax, std::size_t steps);

    /// Add a new color to the palette.
    /// \param col The color to be added.
    /// \return the palette builder object (fluent interface)
    [[nodiscard]] PaletteBuilder& addColor(jt::Color const& col);

    /// Add colors from a sprite
    /// \param sprite the sprite from which colors are added
    /// \return the palette builder object (fluent interface)
    [[nodiscard]] PaletteBuilder& addColorsFromPicture(jt::Sprite& sprite);

    /// Add colors from the palette of an aseprite file
    /// \param filepath path to the aseprite file
    /// \return the palette builder object (fluent interface)
    [[nodiscard]] PaletteBuilder& addColorsFromAseprite(std::string const& filepath);

    /// Make the colors unique
    /// \return the palette builder object
    [[nodiscard]] PaletteBuilder& makeUnique();

    ///
    /// \param function
    /// \return
    [[nodiscard]] PaletteBuilder& applyToPalette(
        std::function<jt::Color(jt::Color const&)> const& function);

private:
    std::vector<Color> m_colors {};
};

} // namespace jt

#endif // JAMTEMPLATE_PALETTE_BUILDER_HPP
