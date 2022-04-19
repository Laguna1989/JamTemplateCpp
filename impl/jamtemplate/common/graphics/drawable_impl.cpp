﻿#include "drawable_impl.hpp"
#include <iostream>

jt::Vector2f jt::DrawableImpl::m_CamOffset { 0.0f, 0.0f };

void jt::DrawableImpl::draw(std::shared_ptr<jt::RenderTarget> sptr) const
{
    if (!m_hasBeenUpdated) {
        std::cout << "WARNING: Calling DrawableImpl::draw() without previous call to "
                     "DrawableImpl::update()!\n";
    }
    if (!sptr) {
        return;
    }
    if (isVisible()) {
        drawShadow(sptr);
        doDraw(sptr);
        drawFlash(sptr);
    }
}

void jt::DrawableImpl::flash(float t, jt::Color col) { doFlash(t, col); }

void jt::DrawableImpl::shake(float t, float strength, float shakeInterval)
{
    doShake(t, strength, shakeInterval);
}

void jt::DrawableImpl::update(float elapsed)
{
    updateShake(elapsed);
    updateFlash(elapsed);
    doUpdate(elapsed);
    m_hasBeenUpdated = true;
}

jt::Vector2f jt::DrawableImpl::getOffset() const { return m_offset; }
void jt::DrawableImpl::setOffset(jt::Vector2f const offset) { m_offset = offset; }

void jt::DrawableImpl::setRotation(float rot) { doSetRotation(rot); }
float jt::DrawableImpl::getRotation() const { return doGetRotation(); }

void jt::DrawableImpl::setShadowActive(bool active) { doSetShadowActive(active); }

bool jt::DrawableImpl::getShadowActive() const { return doGetShadowActive(); }
jt::Color jt::DrawableImpl::getShadowColor() const { return doGetShadowColor(); }
jt::Vector2f jt::DrawableImpl::getShadowOffset() const { return doGetShadowOffset(); }

void jt::DrawableImpl::setIgnoreCamMovement(bool ignore) { m_ignoreCamMovement = ignore; }

void jt::DrawableImpl::setShadow(jt::Color const& col, jt::Vector2f const& offset)
{
    doSetShadow(col, offset);
}

jt::Vector2f jt::DrawableImpl::getShakeOffset() const { return doGetShakeOffset(); }

jt::Vector2f jt::DrawableImpl::getCamOffset() const
{
#if USE_SFML
    return (m_ignoreCamMovement ? -1.0f * jt::DrawableImpl::getStaticCamOffset()
                                : jt::Vector2f { 0.0f, 0.0f });
#else
    return (m_ignoreCamMovement ? jt::Vector2f { 0.0f, 0.0f }
                                : 1.0 * jt::DrawableImpl::getStaticCamOffset());
#endif
}

bool jt::DrawableImpl::getIgnoreCamMovement() const { return m_ignoreCamMovement; }

void jt::DrawableImpl::setCamOffset(const jt::Vector2f& v) { m_CamOffset = v; }
jt::Vector2f jt::DrawableImpl::getStaticCamOffset() { return m_CamOffset; }

void jt::DrawableImpl::setFlashColor(jt::Color const& col) { doSetFlashColor(col); }
jt::Color jt::DrawableImpl::getFlashColor() const { return doGetFlashColor(); }

void jt::DrawableImpl::setScreenSizeHint(jt::Vector2f const& hint) { m_screenSizeHint = hint; }

bool jt::DrawableImpl::isVisible() const
{
    if (m_screenSizeHint.x == 0 && m_screenSizeHint.y == 0) {
        return true;
    }

    jt::Vector2f const camOffset = getStaticCamOffset();
    if (getPosition().x + camOffset.x + getLocalBounds().width < 0) {
        return false;
    }
    if (getPosition().y + camOffset.y + getLocalBounds().height < 0) {
        return false;
    }
    if (getPosition().x + camOffset.x >= this->m_screenSizeHint.x + getLocalBounds().width) {
        return false;
    }
    if (getPosition().y + camOffset.y >= this->m_screenSizeHint.y + getLocalBounds().height) {
        return false;
    }
    return true;
}
void jt::DrawableImpl::setBlendMode(jt::BlendMode mode) { m_blendMode = mode; }
jt::BlendMode jt::DrawableImpl::getBlendMode() const { return m_blendMode; }
