#ifndef JAMTEMPLATE_VECTOR_HPP_INCLUDE_GUARD
#define JAMTEMPLATE_VECTOR_HPP_INCLUDE_GUARD

#include <iosfwd>

namespace jt {

struct Vector2f {
    constexpr Vector2f() noexcept
        : x { 0.0f }
        , y { 0.0f }
    {
    }

    constexpr Vector2f(float x, float y) noexcept
        : x { x }
        , y { y }
    {
    }

    float x { 0.0f };
    float y { 0.0f };

    constexpr bool operator==(jt::Vector2f const& other) const = default;
    constexpr bool operator!=(jt::Vector2f const& other) const = default;
};

constexpr jt::Vector2f operator+(jt::Vector2f const& a, jt::Vector2f const& b) noexcept
{
    return jt::Vector2f { a.x + b.x, a.y + b.y };
}

constexpr jt::Vector2f operator-(jt::Vector2f const& a, jt::Vector2f const& b) noexcept
{
    return jt::Vector2f { a.x - b.x, a.y - b.y };
}

// Note: operator += and -= modify the state, so it makes no sense to have them constexpr

jt::Vector2f& operator+=(jt::Vector2f& lhs, jt::Vector2f const& rhs) noexcept;
jt::Vector2f& operator-=(jt::Vector2f& lhs, jt::Vector2f const& rhs) noexcept;
jt::Vector2f& operator*=(jt::Vector2f& lhs, float const& rhs) noexcept;

constexpr jt::Vector2f operator*(float const f, jt::Vector2f const& v) noexcept
{
    return jt::Vector2f { f * v.x, f * v.y };
};

constexpr jt::Vector2f operator*(jt::Vector2f const& v, float const f) noexcept { return f * v; };

constexpr jt::Vector2f operator/(jt::Vector2f const& v, float const f)
{
    return jt::Vector2f { v.x / f, v.y / f };
};

std::ostream& operator<<(std::ostream& os, Vector2f const& vec);

////
///
///
///

struct Vector2u {
    constexpr Vector2u() noexcept
        : x { 0u }
        , y { 0u }
    {
    }

    constexpr Vector2u(unsigned int x, unsigned int y) noexcept
        : x { x }
        , y { y }
    {
    }

    unsigned int x { 0u };
    unsigned int y { 0u };

    constexpr bool operator==(jt::Vector2u const& other) const = default;
    constexpr bool operator!=(jt::Vector2u const& other) const = default;
};

constexpr jt::Vector2u operator+(jt::Vector2u const& a, jt::Vector2u const& b) noexcept
{
    return jt::Vector2u { a.x + b.x, a.y + b.y };
}

constexpr jt::Vector2u operator-(jt::Vector2u const& a, jt::Vector2u const& b) noexcept
{
    return jt::Vector2u { a.x - b.x, a.y - b.y };
}

jt::Vector2u& operator+=(jt::Vector2u& lhs, jt::Vector2u const& other);

jt::Vector2u& operator-=(jt::Vector2u& lhs, jt::Vector2u const& other);

std::ostream& operator<<(std::ostream& os, Vector2u const& vec);

} // namespace jt

#endif
