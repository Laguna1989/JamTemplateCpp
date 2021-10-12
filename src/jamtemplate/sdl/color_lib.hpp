#ifndef GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_COLOR_LIB_GUARD_HPP

#include "color_base.hpp"
#include <SDL2/SDL.h>

namespace jt {

class Color final : public ColorBase {
public:
    Color()
        : m_color { 0, 0, 0, 255 }
    {
    }
    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
        : m_color { r, g, b, a }
    {
    }

    Color(SDL_Color const& v)
        : m_color { v }
    {
    }

    ~Color() = default;
    Color(jt::Color const&) = default;
    Color(jt::Color&&) = default;

    Color& operator=(jt::Color const&) = default;
    Color& operator=(jt::Color&&) = default;

    operator SDL_Color() const { return m_color; }

    std::uint8_t r() const override { return m_color.r; };
    std::uint8_t g() const override { return m_color.g; };
    std::uint8_t b() const override { return m_color.b; };
    std::uint8_t a() const override { return m_color.a; };

    std::uint8_t& r() override { return m_color.r; };
    std::uint8_t& g() override { return m_color.g; };
    std::uint8_t& b() override { return m_color.b; };
    std::uint8_t& a() override { return m_color.a; };

private:
    SDL_Color m_color;
};

} // namespace jt

#endif
