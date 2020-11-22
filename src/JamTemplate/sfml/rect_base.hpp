#ifndef RECT_BASE_GUARD_HPP
#define RECT_BASE_GUARD_HPP

#include <SFML/Graphics/Rect.hpp>

namespace jt {

class rect final {
public:
    rect()
        : m_rect { 0.0f, 0.0f, 0.0f, 0.0f }
    {
    }
    rect(float left, float top, float width, float height)
        : m_rect { left, top, width, height }
    {
    }

    rect(sf::FloatRect const& v)
        : m_rect { v }
    {
    }

    ~rect() = default;
    rect(jt::rect const&) = default;
    rect(jt::rect&&) = default;

    rect& operator=(jt::rect const&) = default;
    rect& operator=(jt::rect&&) = default;

    operator sf::FloatRect() const { return m_rect; }

    sf::FloatRect m_rect;

    float left() const { return m_rect.left; };
    float top() const { return m_rect.top; };
    float width() const { return m_rect.width; };
    float height() const { return m_rect.height; };

    float& left() { return m_rect.left; };
    float& top() { return m_rect.top; };
    float& width() { return m_rect.width; };
    float& height() { return m_rect.height; };
};

} // namespace jt

#endif
