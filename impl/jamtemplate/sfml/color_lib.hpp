#ifndef GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP

#include "color_base.hpp"
#include <SFML/Graphics/Color.hpp>

namespace jt {

/// Class for storing a color
class Color final : public jt::ColorBase {
public:
    /// Default Constructor, will initialize the color to black
    Color();
    /// Constructor
    /// \param r red value [0-255]
    /// \param g green value [0-255]
    /// \param b blue value [0-255]
    /// \param a alpha value [0-255]
    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);

    /// Conversion from sf::Color
    /// \param v
    Color(sf::Color const& v);

    /// Destructor
    ~Color() = default;

    Color(jt::Color const&) = default;
    Color(jt::Color&&) = default;

    Color& operator=(jt::Color const&) = default;
    Color& operator=(jt::Color&&) = default;

    /// Conversion to sf::Color
    /// \return
    operator sf::Color() const;

    /// Access red
    /// \return red
    std::uint8_t r() const override;

    /// Acces green
    /// \return green
    std::uint8_t g() const override;

    /// Access blue
    /// \return blue
    std::uint8_t b() const override;

    /// Access alpha
    /// \return alpha
    std::uint8_t a() const override;

    /// Access red
    /// \return red
    std::uint8_t& r() override;

    /// Acces green
    /// \return green
    std::uint8_t& g() override;

    /// Access blue
    /// \return blue
    std::uint8_t& b() override;

    /// Access alpha
    /// \return alpha
    std::uint8_t& a() override;

private:
    sf::Color m_color;
};

} // namespace jt

#endif
