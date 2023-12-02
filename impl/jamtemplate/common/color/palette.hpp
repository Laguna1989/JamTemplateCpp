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

    /// Get the number of colors in the palette.
    /// \return the number of colors
    std::size_t size() const noexcept;

    /// Check if the palette contains any colors.
    /// \return true if empty, falso otherwise
    bool empty() const noexcept;

    /// Get a color from the palette. Will raise an exception if index is out of bounds.
    /// \param idx the index of the color
    /// \return the Color
    jt::Color const& getColor(std::size_t idx) const;

private:
    std::vector<jt::Color> m_colors;
};

} // namespace jt

#endif // JAMTEMPLATE_PALETTE_HPP
