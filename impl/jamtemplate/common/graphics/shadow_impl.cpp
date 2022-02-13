#include "shadow_impl.hpp"

namespace jt {

void ShadowImpl::doSetShadow(Color const& col, Vector2f const& offset)
{
    m_shadowActive = true;
    m_shadowColor = col;
    m_shadowOffset = offset;
}

void ShadowImpl::drawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (sptr) {
        if (m_shadowActive) {
            doDrawShadow(sptr);
        }
    }
}

void ShadowImpl::doSetShadowActive(bool active) { m_shadowActive = active; }

bool ShadowImpl::doGetShadowActive() const { return m_shadowActive; }
jt::Color ShadowImpl::doGetShadowColor() const { return m_shadowColor; }
jt::Vector2f ShadowImpl::doGetShadowOffset() const { return m_shadowOffset; }

} // namespace jt
