#ifndef COLOR_BASE_GUARD_HPP
#define COLOR_BASE_GUARD_HPP

#include <SDL.h>
#include <cstdint>

namespace jt {

class color final {
public:
    color()
        : m_col { 0, 0, 0, 255 }
    {
    }
    color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
        : m_col { r, g, b, a }
    {
    }

    color(SDL_Color const& v)
        : m_col { v }
    {
    }

    ~color() = default;
    color(jt::color const&) = default;
    color(jt::color&&) = default;

    color& operator=(jt::color const&) = default;
    color& operator=(jt::color&&) = default;

    operator SDL_Color() const { return m_col; }

    SDL_Color m_col;

    std::uint8_t r() const { return m_col.r; };
    std::uint8_t g() const { return m_col.g; };
    std::uint8_t b() const { return m_col.b; };
    std::uint8_t a() const { return m_col.a; };

    std::uint8_t& r() { return m_col.r; };
    std::uint8_t& g() { return m_col.g; };
    std::uint8_t& b() { return m_col.b; };
    std::uint8_t& a() { return m_col.a; };
};

} // namespace jt

#endif
