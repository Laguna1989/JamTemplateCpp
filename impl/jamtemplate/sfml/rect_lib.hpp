#ifndef GUARD_JAMTEMPLATE_RECT_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_RECT_LIB_GUARD_HPP

#include "rect_base.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace jt {

/// Rect class
class Rect final : public rectBase {
public:
    /// Default constructor, initializes all members to 0
    Rect()
        : m_rect { 0.0f, 0.0f, 0.0f, 0.0f }
    {
    }

    /// Constructor
    /// \param left left value
    /// \param top top value
    /// \param width width value
    /// \param height height value
    Rect(float left, float top, float width, float height)
        : m_rect { left, top, width, height }
    {
    }

    /// Construct from sf::FloatRect
    /// \param v
    Rect(sf::FloatRect const& v)
        : m_rect { v }
    {
    }

    /// Destructor
    ~Rect() = default;
    Rect(jt::Rect const&) = default;

    Rect& operator=(jt::Rect const&) = default;
    Rect& operator=(jt::Rect&&) = default;

    /// Conversion to sf::FloatRect
    operator sf::FloatRect() const { return m_rect; }

    float left() const override { return m_rect.left; };
    float top() const override { return m_rect.top; };
    float width() const override { return m_rect.width; };
    float height() const override { return m_rect.height; };
    float& left() override { return m_rect.left; };
    float& top() override { return m_rect.top; };
    float& width() override { return m_rect.width; };
    float& height() override { return m_rect.height; };

private:
    sf::FloatRect m_rect;
};

class Recti final : public rectiBase {
public:
    Recti()
        : Recti { 0, 0, 0, 0 }
    {
    }
    Recti(int left, int top, int width, int height)
        : m_rect { left, top, width, height }
    {
    }

    Recti(sf::IntRect const& v)
        : m_rect { v }
    {
    }

    ~Recti() = default;
    Recti(jt::Recti const&) = default;
    Recti(jt::Recti&&) = default;

    Recti& operator=(jt::Recti const&) = default;
    Recti& operator=(jt::Recti&&) = default;

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
