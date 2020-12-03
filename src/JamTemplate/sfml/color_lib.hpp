#ifndef GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP

#include "color_base.hpp"
#include <SFML/Graphics/Color.hpp>

namespace jt {

class color final : public jt::colorBase {
public:
    color()
        : m_col { 0, 0, 0, 255 }
    {
    }
    color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
        : m_col { r, g, b, a }
    {
    }

    color(sf::Color const& v)
        : m_col { v }
    {
    }

    ~color() = default;
    color(jt::color const&) = default;
    color(jt::color&&) = default;

    color& operator=(jt::color const&) = default;
    color& operator=(jt::color&&) = default;

    operator sf::Color() const { return m_col; }

    sf::Color m_col;

    std::uint8_t r() const override { return m_col.r; };
    std::uint8_t g() const override { return m_col.g; };
    std::uint8_t b() const override { return m_col.b; };
    std::uint8_t a() const override { return m_col.a; };

    std::uint8_t& r() override { return m_col.r; };
    std::uint8_t& g() override { return m_col.g; };
    std::uint8_t& b() override { return m_col.b; };
    std::uint8_t& a() override { return m_col.a; };
};

} // namespace jt

#endif
