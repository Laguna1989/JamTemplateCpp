#ifndef GUARD_JAMTEMPLATE_SMARTDRAWABLE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTDRAWABLE_HPP_INCLUDEGUARD

#include "Lerp.hpp"
#include "Random.hpp"
#include "rendertarget.hpp"
#include "vector.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace jt {
class SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartDrawable>;

    virtual ~SmartDrawable() = default;

    void draw(std::shared_ptr<jt::renderTarget> sptr) const
    {
        if (m_hasBeenUpdated == false) {
            std::cout << "WARNING: Calling SmartDrawable::draw() without previous call to "
                         "SmartDrawable::update()!\n";
        }

        if (m_shadowActive) {
            doDrawShadow(sptr);
        }

        doDraw(sptr);
        if (m_flashTimer > 0) {
            doDrawFlash(sptr);
        }
    }

    void flash(float t, jt::color col = jt::colors::White)
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

    virtual void setColor(jt::color const& col) = 0;
    virtual const jt::color getColor() const = 0;

    virtual void setPosition(jt::vector2 const& pos) = 0;
    virtual const jt::vector2 getPosition() const = 0;

    // virtual sf::Transform const getTransform() const = 0;
    virtual jt::rect const getGlobalBounds() const = 0;
    virtual jt::rect const getLocalBounds() const = 0;

    virtual void setFlashColor(jt::color const& col) = 0;
    virtual const jt::color getFlashColor() const = 0;

    virtual void setScale(jt::vector2 const& scale) = 0;
    virtual const jt::vector2 getScale() const = 0;

    virtual void setOrigin(jt::vector2 const& origin) = 0;
    virtual const jt::vector2 getOrigin() const = 0;

    jt::vector2 getOffset() const { return m_offset; }

    void setOffset(jt::vector2 const offset) { m_offset = offset; }

    void setRotation(float rot)
    {
        m_rotationInDegree = rot;
        doRotate(rot);
    }

    float getRotation() const { return m_rotationInDegree; }

    virtual void setShadowActive(bool active) { m_shadowActive = active; }
    bool getShadowActive() const { return m_shadowActive; }
    virtual void setShadowColor(jt::color const& col) { m_shadowColor = col; }
    jt::color const getShadowColor() const { return m_shadowColor; }
    virtual void setShadowOffset(jt::vector2 const& v) { m_shadowOffset = v; }
    jt::vector2 const getShadowOffset() const { return m_shadowOffset; }

    // do not call this manually. Only place to call is Game()->update();
    static void setCamOffset(jt::vector2 const& v) { m_CamOffset = v; }

    void setIgnoreCamMovement(bool ignore) { m_ignoreCamMovement = ignore; }

    void setShadow(jt::color const& col, jt::vector2 const& offset)
    {
        setShadowActive(true);
        setShadowColor(col);
        setShadowOffset(offset);
    }

    float getZDist() const { return m_zdist; }
    void setZDist(float const v) { m_zdist = v; }

protected:
    jt::vector2 getShakeOffset() const { return m_shakeOffset; }

    jt::vector2 getCamOffset() const
    {
        return (m_ignoreCamMovement ? m_CamOffset : jt::vector2 { 0.0f, 0.0f });
    }
    bool getIgnoreCamMovement() const { return m_ignoreCamMovement; }

private:
    static jt::vector2 m_CamOffset;
    bool m_ignoreCamMovement { false };

    bool m_hasBeenUpdated { false };
    float m_flashTimer { -1.0f };
    float m_maxFlashTimer { -1.0f };

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::vector2 m_shakeOffset { 0, 0 };

    jt::vector2 m_offset { 0, 0 };
    float m_rotationInDegree { 0 };

    bool m_shadowActive { false };
    jt::vector2 m_shadowOffset { 0.0f, 0.0f };
    jt::color m_shadowColor { jt::colors::Black };

    float m_zdist { 0.0f };

    virtual void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const = 0;
    virtual void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const = 0;
    virtual void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const = 0;

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) = 0;
    virtual void doFlash(float /*t*/, jt::color /*col = jt::colors::White*/) { }
    virtual void doRotate(float /*rot*/) = 0;

    void updateFlash(float elapsed)
    {
        if (m_flashTimer > 0) {
            m_flashTimer -= elapsed;
            auto col = getFlashColor();
            float a = Lerp::linear((float)col.a(), 0.0f, 1.0f - (m_flashTimer / m_maxFlashTimer));
            col.a() = static_cast<std::uint8_t>(a);
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
                m_shakeOffset.x() = Random::getFloat(-m_shakeStrength, m_shakeStrength);
                m_shakeOffset.y() = Random::getFloat(-m_shakeStrength, m_shakeStrength);
            }
        } else {
            m_shakeOffset.x() = m_shakeOffset.y() = 0;
        }
    }
};
} // namespace jt

#endif
