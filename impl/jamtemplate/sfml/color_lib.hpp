#ifndef GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP

#include "color_base.hpp"
#include <SFML/Graphics/Color.hpp>

namespace jt {

/// Class for storing a color
class Color final : public jt::ColorBase {
public:
    /// Default Constructor, will initialize the color to black
    Color()
        : m_color { 0, 0, 0, 255 }
    {
    }
    /// Constructor
    /// \param r red
    /// \param g green
    /// \param b blue
    /// \param a alpha
    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
        : m_color { r, g, b, a }
    {
    }

    /// Conversion from sf::Color
    /// \param v
    Color(sf::Color const& v)
        : m_color { v }
    {
    }

    /// Destructor
    ~Color() = default;

    Color(jt::Color const&) = default;
    Color(jt::Color&&) = default;

    Color& operator=(jt::Color const&) = default;
    Color& operator=(jt::Color&&) = default;

    /// Conversion to sf::Color
    /// \return
    operator sf::Color() const { return m_color; }

    /// Access red
    /// \return red
    std::uint8_t r() const override { return m_color.r; };

    /// Acces green
    /// \return green
    std::uint8_t g() const override { return m_color.g; };

    /// Access blue
    /// \return blue
    std::uint8_t b() const override { return m_color.b; };

    /// Access alpha
    /// \return alpha
    std::uint8_t a() const override { return m_color.a; };

    /// Access red
    /// \return red
    std::uint8_t& r() override { return m_color.r; };

    /// Acces green
    /// \return green
    std::uint8_t& g() override { return m_color.g; };

    /// Access blue
    /// \return blue
    std::uint8_t& b() override { return m_color.b; };

    /// Access alpha
    /// \return alpha
    std::uint8_t& a() override { return m_color.a; };

private:
    sf::Color m_color;
};

} // namespace jt

#endif
