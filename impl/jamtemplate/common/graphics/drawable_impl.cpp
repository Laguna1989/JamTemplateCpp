#include "drawable_impl.hpp"
#include <iostream>

namespace jt {

jt::Vector2f DrawableImpl::m_CamOffset { 0.0f, 0.0f };

void DrawableImpl::draw(std::shared_ptr<jt::RenderTarget> sptr) const
{
    if (!m_hasBeenUpdated) {
        std::cout << "WARNING: Calling DrawableImpl::draw() without previous call to "
                     "DrawableImpl::update()!\n";
    }

    if (isVisible()) {
        drawShadow(sptr);
        doDraw(sptr);
        drawFlash(sptr);
    }
}

void DrawableImpl::flash(float t, jt::Color col) { doFlash(t, col); }

void DrawableImpl::shake(float t, float strength, float shakeInterval)
{
    doShake(t, strength, shakeInterval);
}

void DrawableImpl::update(float elapsed)
{
    updateShake(elapsed);
    updateFlash(elapsed);
    doUpdate(elapsed);
    m_hasBeenUpdated = true;
}

jt::Vector2f DrawableImpl::getOffset() const { return m_offset; }
void DrawableImpl::setOffset(jt::Vector2f const offset) { m_offset = offset; }

void DrawableImpl::setRotation(float rot) { doSetRotation(rot); }
float DrawableImpl::getRotation() const { return doGetRotation(); }

void DrawableImpl::setShadowActive(bool active) { doSetShadowActive(active); }

bool DrawableImpl::getShadowActive() const { return doGetShadowActive(); }
jt::Color DrawableImpl::getShadowColor() const { return doGetShadowColor(); }
jt::Vector2f DrawableImpl::getShadowOffset() const { return doGetShadowOffset(); }

void DrawableImpl::setIgnoreCamMovement(bool ignore) { m_ignoreCamMovement = ignore; }

void DrawableImpl::setShadow(jt::Color const& col, jt::Vector2f const& offset)
{
    doSetShadow(col, offset);
}

jt::Vector2f DrawableImpl::getShakeOffset() const { return doGetShakeOffset(); }

jt::Vector2f DrawableImpl::getCamOffset() const
{
#if USE_SFML
    return (m_ignoreCamMovement ? -1.0f * DrawableImpl::getStaticCamOffset()
                                : jt::Vector2f { 0.0f, 0.0f });
#else
    return (m_ignoreCamMovement ? jt::Vector2f { 0.0f, 0.0f }
                                : 1.0 * DrawableImpl::getStaticCamOffset());
#endif
}

bool DrawableImpl::getIgnoreCamMovement() const { return m_ignoreCamMovement; }

void DrawableImpl::setCamOffset(const jt::Vector2f& v) { m_CamOffset = v; }
jt::Vector2f DrawableImpl::getStaticCamOffset() { return m_CamOffset; }

void DrawableImpl::setFlashColor(Color const& col) { doSetFlashColor(col); }
Color DrawableImpl::getFlashColor() const { return doGetFlashColor(); }

void DrawableImpl::setScreenSizeHint(Vector2f const& hint) { m_screenSizeHint = hint; }

bool DrawableImpl::isVisible() const
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

} // namespace jt
