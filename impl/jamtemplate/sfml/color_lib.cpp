#include "color_lib.hpp"

namespace jt {

Color::Color()
    : m_color { 0, 0, 0, 255 }
{
}
Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
    : m_color { r, g, b, a }
{
}

Color::Color(sf::Color const& v)
    : m_color { v }
{
}

Color::operator sf::Color() const { return m_color; }

std::uint8_t Color::r() const { return m_color.r; }

std::uint8_t Color::g() const { return m_color.g; }
std::uint8_t Color::b() const { return m_color.b; }
std::uint8_t Color::a() const { return m_color.a; }
std::uint8_t& Color::r() { return m_color.r; }
std::uint8_t& Color::g() { return m_color.g; }
std::uint8_t& Color::b() { return m_color.b; }
std::uint8_t& Color::a() { return m_color.a; }

} // namespace jt
