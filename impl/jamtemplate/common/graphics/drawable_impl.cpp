#include "drawable_impl.hpp"
#include <iostream>

jt::Vector2f jt::DrawableImpl::m_CamOffset { 0.0f, 0.0f };

void jt::DrawableImpl::draw(std::shared_ptr<jt::RenderTargetInterface> targetContainer) const
{
    if (!m_hasBeenUpdated) [[unlikely]] {
        std::cout << "WARNING: Calling DrawableImpl::draw() without previous call to "
                     "DrawableImpl::update()!\n";
    }
    if (!targetContainer) [[unlikely]] {
        return;
    }
    auto const sptr = targetContainer->get(m_z);
    if (sptr) [[likely]] {
        draw(sptr);
    }
}

void jt::DrawableImpl::draw(std::shared_ptr<RenderTargetLayer> sptr) const
{
    if (isVisible()) {
        if (allowDrawFromFlicker()) {
            drawShadow(sptr);
            drawOutline(sptr);
            doDraw(sptr);
            drawFlash(sptr);
        }
    }
}

void jt::DrawableImpl::flash(float t, jt::Color col) { doFlash(t, col); }

void jt::DrawableImpl::shake(float t, float strength, float shakeInterval)
{
    doShake(t, strength, shakeInterval);
}

void jt::DrawableImpl::flicker(float duration, float interval) { doFlicker(duration, interval); }

void jt::DrawableImpl::update(float elapsed)
{
    updateShake(elapsed);
    updateFlash(elapsed);
    updateFlicker(elapsed);
    doUpdate(elapsed);
    m_hasBeenUpdated = true;
}

jt::Vector2f jt::DrawableImpl::getOffset() const { return m_offset; }

void jt::DrawableImpl::setOffset(jt::Vector2f const& offset)
{
    m_offset = offset;
    m_offsetMode = jt::OffsetMode::MANUAL;
}

jt::OffsetMode jt::DrawableImpl::getOffsetMode() const { return m_offsetMode; }

void jt::DrawableImpl::setOffset(jt::OffsetMode offset)
{
    m_offsetMode = offset;
    if (m_offsetMode == OffsetMode::TOPLEFT) {
        m_offset = jt::Vector2f {};
    } else if (m_offsetMode == OffsetMode::CENTER) {
        m_offset = jt::Vector2f { -0.5f * getLocalBounds().width, -0.5f * getLocalBounds().height };
    }
}

void jt::DrawableImpl::setOrigin(jt::Vector2f const& origin)
{
    m_origin = origin;
    m_originMode = jt::OriginMode::MANUAL;
    setOriginInternal(m_origin);
}

jt::OriginMode jt::DrawableImpl::getOriginMode() const { return m_originMode; }

void jt::DrawableImpl::setOrigin(jt::OriginMode origin)
{
    m_originMode = origin;
    if (m_originMode == OriginMode::TOPLEFT) {
        m_origin = jt::Vector2f {};
    } else if (m_originMode == OriginMode::CENTER) {
        m_origin = jt::Vector2f { 0.5f * getLocalBounds().width, 0.5f * getLocalBounds().height };
    }
    setOriginInternal(m_origin);
}

jt::Vector2f jt::DrawableImpl::getOrigin() const { return m_origin; }

void jt::DrawableImpl::setRotation(float rot) { doSetRotation(rot); }

float jt::DrawableImpl::getRotation() const { return doGetRotation(); }

void jt::DrawableImpl::setShadowActive(bool active) { doSetShadowActive(active); }

bool jt::DrawableImpl::getShadowActive() const { return doGetShadowActive(); }

jt::Color jt::DrawableImpl::getShadowColor() const { return doGetShadowColor(); }

jt::Vector2f jt::DrawableImpl::getShadowOffset() const { return doGetShadowOffset(); }

void jt::DrawableImpl::setIgnoreCamMovement(bool ignore)
{
    m_ignoreCamMovement = ignore;
    if (m_ignoreCamMovement) {
        m_camMovementFactor = 0.0f;
    }
}

void jt::DrawableImpl::setShadow(jt::Color const& col, jt::Vector2f const& offset)
{
    doSetShadow(col, offset);
}

void jt::DrawableImpl::setOutline(jt::Color const& col, int width) { doSetOutline(col, width); }

jt::Vector2f jt::DrawableImpl::getShakeOffset() const { return doGetShakeOffset(); }

jt::Vector2f jt::DrawableImpl::getCamOffset() const
{
#if USE_SFML
    auto const value = (m_ignoreCamMovement ? -1.0f * jt::DrawableImpl::getStaticCamOffset()
                                            : jt::Vector2f { 0.0f, 0.0f });
    return value;
#else
    return (m_ignoreCamMovement ? jt::Vector2f { 0.0f, 0.0f }
                                : 1.0 * jt::DrawableImpl::getStaticCamOffset());
#endif
}

bool jt::DrawableImpl::getIgnoreCamMovement() const { return m_ignoreCamMovement; }

void jt::DrawableImpl::setCamOffset(jt::Vector2f const& v) { m_CamOffset = v; }

jt::Vector2f jt::DrawableImpl::getStaticCamOffset() { return m_CamOffset; }

void jt::DrawableImpl::setFlashColor(jt::Color const& col) { doSetFlashColor(col); }

jt::Color jt::DrawableImpl::getFlashColor() const { return doGetFlashColor(); }

void jt::DrawableImpl::setScreenSizeHint(jt::Vector2f const& hint) { m_screenSizeHint = hint; }

bool jt::DrawableImpl::isVisible() const
{
    if (m_screenSizeHint.x == 0 && m_screenSizeHint.y == 0) {
        return true;
    }

    jt::Vector2f const camOffset = getStaticCamOffset() * m_camMovementFactor;
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

jt::Vector2f jt::DrawableImpl::getScreenPosition() const
{
    auto const camOffset = getStaticCamOffset();
    return getPosition() + camOffset * m_camMovementFactor;
}

jt::Vector2f jt::DrawableImpl::getScreenSizeHint() const { return m_screenSizeHint; }

void jt::DrawableImpl::setCamMovementFactor(float factor)
{
    m_camMovementFactor = factor;
    bool const ignoreCamMovement = m_camMovementFactor != 1.0f;
    m_ignoreCamMovement = ignoreCamMovement;
}

float jt::DrawableImpl::getCamMovementFactor() const { return m_camMovementFactor; }

void jt::DrawableImpl::setZ(int z) { m_z = z; }

int jt::DrawableImpl::getZ() const { return m_z; }

bool jt::DrawableImpl::getOutlineActive() const { return getOutlineWidth() != 0; }

jt::Color jt::DrawableImpl::getOutlineColor() const { return doGetOutlineColor(); }

int jt::DrawableImpl::getOutlineWidth() const { return doGetOutlineWidth(); }

std::vector<jt::Vector2f> jt::DrawableImpl::getOutlineOffsets() const
{
    return doGetOutlineOffsets();
}
