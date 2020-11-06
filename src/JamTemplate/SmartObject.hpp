#ifndef JAMTEMPLATE_SMARTOBJECT_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTOBJECT_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Lerp.hpp"
#include "Random.hpp"

namespace JamTemplate {
class SmartObject {
public:
    using Sptr = std::shared_ptr<SmartObject>;

    virtual ~SmartObject() = default;

    void draw(std::shared_ptr<sf::RenderTarget> sptr) const
    {
        if (m_hasBeenUpdated == false) {
            std::cout << "WARNING: Calling SmartObject::draw() without previous call to "
                         "SmartObject::update()!\n";
        }

        if (m_shadowActive) {
            doDrawShadow(sptr);
        }

        doDraw(sptr);
        if (m_flashTimer > 0) {
            doDrawFlash(sptr);
        }
    }

    void flash(float t, sf::Color col = sf::Color::White)
    {
        m_maxFlashTimer = m_flashTimer = t;
        setFlashColor(col);
        doFlash(t, col);
    }

    void shake(float t, float strength, float shakeInterval = 0.05f)
    {
        m_shakeTimer = t;
        m_shakeStrength = strength;
        m_shakeInterval = m_shakeIntervalMax = shakeInterval;
    }

    void update(float elapsed)
    {
        updateShake(elapsed);
        updateFlash(elapsed);
        doUpdate(elapsed);
        m_hasBeenUpdated = true;
    }

    virtual void setColor(sf::Color const& col) = 0;
    virtual const sf::Color getColor() const = 0;

    virtual void setPosition(sf::Vector2f const& pos) = 0;
    virtual const sf::Vector2f getPosition() const = 0;

    virtual sf::Transform const getTransform() const = 0;
    virtual sf::FloatRect const getGlobalBounds() const = 0;
    virtual sf::FloatRect const getLocalBounds() const = 0;

    virtual void setFlashColor(sf::Color const& col) = 0;
    virtual const sf::Color getFlashColor() const = 0;

    virtual void setScale(sf::Vector2f const& scale) = 0;
    virtual const sf::Vector2f getScale() const = 0;

    virtual void setOrigin(sf::Vector2f const& origin) = 0;
    virtual const sf::Vector2f getOrigin() const = 0;

    sf::Vector2f getOffset() const { return m_offset; }

    void setOffset(sf::Vector2f const offset) { m_offset = offset; }

    void setRotation(float rot)
    {
        m_rotationInDegree = rot;
        doRotate(rot);
    }

    float getRotation() const { return m_rotationInDegree; }

    virtual void setShadowActive(bool active) { m_shadowActive = active; }
    bool getShadowActive() const { return m_shadowActive; }
    virtual void setShadowColor(sf::Color const& col) { m_shadowColor = col; }
    sf::Color const getShadowColor() const { return m_shadowColor; }
    virtual void setShadowOffset(sf::Vector2f const& v) { m_shadowOffset = v; }
    sf::Vector2f const getShadowOffset() const { return m_shadowOffset; }

    // do not call this manually. Only place to call is Game()->update();
    static void setCamOffset(sf::Vector2f const& v) { m_CamOffset = v; }

    void setIgnoreCamMovement(bool ignore) { m_ignoreCamMovement = ignore; }

    void setShadow(sf::Color const& col, sf::Vector2f const& offset)
    {
        setShadowActive(true);
        setShadowColor(col);
        setShadowOffset(offset);
    }

protected:
    sf::Vector2f getShakeOffset() const { return m_shakeOffset; }

    sf::Vector2f getCamOffset() const
    {
        return (m_ignoreCamMovement ? m_CamOffset : sf::Vector2f { 0.0f, 0.0f });
    }
    bool getIgnoreCamMovement() const { return m_ignoreCamMovement; }

private:
    static sf::Vector2f m_CamOffset;
    bool m_ignoreCamMovement { false };
    bool m_moveWithCam { true };

    bool m_hasBeenUpdated { false };
    float m_flashTimer { -1.0f };
    float m_maxFlashTimer { -1.0f };

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    sf::Vector2f m_shakeOffset { 0, 0 };

    sf::Vector2f m_offset { 0, 0 };
    float m_rotationInDegree { 0 };

    bool m_shadowActive { false };
    sf::Vector2f m_shadowOffset { 0.0f, 0.0f };
    sf::Color m_shadowColor { sf::Color::Black };

    virtual void doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const = 0;
    virtual void doDrawFlash(std::shared_ptr<sf::RenderTarget> const sptr) const = 0;
    virtual void doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const = 0;

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) = 0;
    virtual void doFlash(float /*t*/, sf::Color /*col = sf::Color::White*/) { }
    virtual void doRotate(float /*rot*/) = 0;

    void updateFlash(float elapsed)
    {
        if (m_flashTimer > 0) {
            m_flashTimer -= elapsed;
            float a = Lerp::linear(255.0f, 0.0f, 1.0f - (m_flashTimer / m_maxFlashTimer));
            auto col = getFlashColor();
            col.a = static_cast<sf::Uint8>(a);
            setFlashColor(col);
        }
    }

    void updateShake(float elapsed)
    {
        if (m_shakeTimer > 0) {
            m_shakeTimer -= elapsed;
            m_shakeInterval -= elapsed;
            if (m_shakeInterval <= 0) {
                m_shakeInterval = m_shakeIntervalMax;
                m_shakeOffset.x = Random::getFloat(-m_shakeStrength, m_shakeStrength);
                m_shakeOffset.y = Random::getFloat(-m_shakeStrength, m_shakeStrength);
            }
        } else {
            m_shakeOffset.x = m_shakeOffset.y = 0;
        }
    }
};
} // namespace JamTemplate

#endif
