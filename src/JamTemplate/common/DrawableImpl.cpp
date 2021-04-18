﻿#include "DrawableImpl.hpp"

namespace jt {

jt::Vector2 DrawableImpl::m_CamOffset { 0.0f, 0.0f };

void DrawableImpl::draw(std::shared_ptr<jt::renderTarget> sptr) const
{
    if (m_hasBeenUpdated == false) {
        std::cout << "WARNING: Calling DrawableImpl::draw() without previous call to "
                     "DrawableImpl::update()!\n";
    }

    if (m_shadowActive) {
        doDrawShadow(sptr);
    }

    doDraw(sptr);
    if (m_flashTimer > 0) {
        doDrawFlash(sptr);
    }
}

void DrawableImpl::flash(float t, jt::Color col)
{
    m_maxFlashTimer = m_flashTimer = t;
    setFlashColor(col);
    doFlash(t, col);
}

void DrawableImpl::shake(float t, float strength, float shakeInterval)
{
    m_shakeTimer = t;
    m_shakeStrength = strength;
    m_shakeInterval = m_shakeIntervalMax = shakeInterval;
}

void DrawableImpl::update(float elapsed)
{
    updateShake(elapsed);
    updateFlash(elapsed);
    doUpdate(elapsed);
    m_hasBeenUpdated = true;
}

jt::Vector2 DrawableImpl::getOffset() const { return m_offset; }
void DrawableImpl::setOffset(jt::Vector2 const offset) { m_offset = offset; }

void DrawableImpl::setRotation(float rot)
{
    m_rotationInDegree = rot;
    doRotate(rot);
}

float DrawableImpl::getRotation() const { return m_rotationInDegree; }

void DrawableImpl::setShadowActive(bool active) { m_shadowActive = active; }

bool DrawableImpl::getShadowActive() const { return m_shadowActive; }

void DrawableImpl::setShadowColor(jt::Color const& col) { m_shadowColor = col; }

jt::Color const DrawableImpl::getShadowColor() const { return m_shadowColor; }
void DrawableImpl::setShadowOffset(jt::Vector2 const& v) { m_shadowOffset = v; }
jt::Vector2 const DrawableImpl::getShadowOffset() const { return m_shadowOffset; }

void DrawableImpl::setIgnoreCamMovement(bool ignore) { m_ignoreCamMovement = ignore; }

void DrawableImpl::setShadow(jt::Color const& col, jt::Vector2 const& offset)
{
    setShadowActive(true);
    setShadowColor(col);
    setShadowOffset(offset);
}

jt::Vector2 DrawableImpl::getShakeOffset() const { return m_shakeOffset; }

jt::Vector2 DrawableImpl::getCamOffset() const
{
#if ENABLE_WEB
    return (m_ignoreCamMovement ? jt::Vector2 { 0.0f, 0.0f }
                                : 1.0 * DrawableImpl::getStaticCamOffset());
#else
    return (m_ignoreCamMovement ? -1.0f * DrawableImpl::getStaticCamOffset()
                                : jt::Vector2 { 0.0f, 0.0f });
#endif
}

bool DrawableImpl::getIgnoreCamMovement() const { return m_ignoreCamMovement; }

void DrawableImpl::updateFlash(float elapsed)
{
    if (m_flashTimer > 0) {
        m_flashTimer -= elapsed;
        auto col = getFlashColor();
        float a = Lerp::linear((float)col.a(), 0.0f, 1.0f - (m_flashTimer / m_maxFlashTimer));
        col.a() = static_cast<std::uint8_t>(a);
        setFlashColor(col);
    }
}

void DrawableImpl::updateShake(float elapsed)
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

} // namespace jt
