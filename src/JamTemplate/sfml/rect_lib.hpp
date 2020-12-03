#ifndef GUARD_JAMTEMPLATE_RECT_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_RECT_LIB_GUARD_HPP

#include "rect_base.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace jt {

class rect final : public rectBase {
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

    float left() const override { return m_rect.left; };
    float top() const override { return m_rect.top; };
    float width() const override { return m_rect.width; };
    float height() const override { return m_rect.height; };
    float& left() override { return m_rect.left; };
    float& top() override { return m_rect.top; };
    float& width() override { return m_rect.width; };
    float& height() override { return m_rect.height; };
};

class recti final : public rectiBase {
public:
    recti()
        : recti { 0, 0, 0, 0 }
    {
    }
    recti(int left, int top, int width, int height)
        : m_rect { left, top, width, height }
    {
    }

    recti(sf::IntRect const& v)
        : m_rect { v }
    {
    }

    ~recti() = default;
    recti(jt::recti const&) = default;
    recti(jt::recti&&) = default;

    recti& operator=(jt::recti const&) = default;
    recti& operator=(jt::recti&&) = default;

    operator sf::IntRect() const { return m_rect; }

    sf::IntRect m_rect;

    int left() const override { return m_rect.left; };
    int top() const override { return m_rect.top; };
    int width() const override { return m_rect.width; };
    int height() const override { return m_rect.height; };
    int& left() override { return m_rect.left; };
    int& top() override { return m_rect.top; };
    int& width() override { return m_rect.width; };
    int& height() override { return m_rect.height; };
};

} // namespace jt

#endif
