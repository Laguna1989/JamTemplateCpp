#ifndef JAMTEMPLATE_RECT_HPP_INCLUDE_GUARD
#define JAMTEMPLATE_RECT_HPP_INCLUDE_GUARD

#include <iosfwd>

namespace jt {

struct Rectf {
    constexpr Rectf() noexcept
        : left { 0.0f }
        , top { 0.0f }
        , width { 0.0f }
        , height { 0.0f }
    {
    }

    constexpr Rectf(float l, float t, float w, float h) noexcept
        : left { l }
        , top { t }
        , width { w }
        , height { h }
    {
    }

    float left { 0.0f };
    float top { 0.0f };
    float width { 0.0f };
    float height { 0.0f };

    constexpr bool operator==(Rectf const& other) const noexcept = default;
    constexpr bool operator!=(Rectf const& other) const noexcept = default;
};

struct Recti {
    constexpr Recti() noexcept
        : left { 0 }
        , top { 0 }
        , width { 0 }
        , height { 0 }
    {
    }

    constexpr Recti(int l, int t, int w, int h) noexcept
        : left { l }
        , top { t }
        , width { w }
        , height { h }
    {
    }

    int left { 0 };
    int top { 0 };
    int width { 0 };
    int height { 0 };

    constexpr bool operator==(Recti const& other) const noexcept = default;
    constexpr bool operator!=(Recti const& other) const noexcept = default;
};

std::ostream& operator<<(std::ostream& os, Rectf const& rect);
std::ostream& operator<<(std::ostream& os, Recti const& rect);

} // namespace jt

#endif
