
#ifndef JAMTEMPLATE_TRANSFORM_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TRANSFORM_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>

namespace JamTemplate {

class Transform {
public:
    using vt = sf::Vector2f;
    using rt = sf::FloatRect;
    Transform() = default;

    explicit Transform(vt p, vt v = vt {}, vt a = vt {})
        : m_position { p }
        , m_velocity { v }
        , m_acceleration { a }
    {
    }

    void updateTransform(float elapsed)
    {
        setToBoundsVelocity();

        m_velocity += m_acceleration * elapsed;
        m_position += m_velocity * elapsed;

        m_velocity.x = m_velocity.x * m_dragVelocity.x;
        m_velocity.y = m_velocity.y * m_dragVelocity.y;

        setToBoundsPosition();
    }

    void setToBoundsPosition()
    {
        setToBounds(m_position, m_boundsPosition, m_useBoundsPosition);
    }
    void setToBoundsVelocity()
    {
        setToBounds(m_velocity, m_boundsVelocity, m_useBoundsVelocity);
    }

    void unsetBoundsPosition()
    {
        m_useBoundsPosition = false;
    }

    void unsetBoundsVelocity()
    {
        m_useBoundsVelocity = false;
    }

    void setPosition(vt const p) { m_position = p; }
    void setVelocity(vt const v) { m_velocity = v; }
    void setAcceleration(vt const a) { m_acceleration = a; }
    void resetAcceleration() { m_acceleration = vt {}; }
    void addAcceleration(vt const a) { m_acceleration += a; }

    vt getPosition() const { return m_position; }
    vt getVelocity() const { return m_velocity; }
    vt getAcceleration() const { return m_acceleration; }

    rt getBoundsPosition() const { return m_boundsPosition; }
    void setBoundsPosition(rt const& r)
    {
        m_useBoundsPosition = true;
        m_boundsPosition = r;
    }
    void resetBoundsPosition() { m_useBoundsPosition = false; }

    rt getBoundsVelocity() const { return m_boundsVelocity; }
    void setBoundsVelocity(rt const& r)
    {
        m_useBoundsVelocity = true;
        m_boundsVelocity = r;
    }
    void resetBoundsVelocity() { m_useBoundsVelocity = false; }

    void setDragVelocity(vt const& drag)
    {
        m_dragVelocity = drag;
    }
    vt getDragVelocity() const { return m_dragVelocity; }

private:
    vt m_position {};
    vt m_velocity {};
    vt m_acceleration {};

    vt m_dragVelocity { 1, 1 };

    rt m_boundsPosition {};
    bool m_useBoundsPosition = false;

    rt m_boundsVelocity {};
    bool m_useBoundsVelocity = false;

    void setToBounds(vt& value, rt const& r, bool const useBounds)
    {
        if (!useBounds)
            return;

        if (value.x < r.left) {
            value = { r.left, value.y };
        }
        if (value.x > r.left + r.width) {
            value = { r.left + r.width, value.y };
        }

        if (value.y < r.top) {
            value = { value.x, r.top };
        }
        if (value.y > r.top + r.height) {
            value = { value.x, r.top + r.height };
        }
    }
};
}
#endif
