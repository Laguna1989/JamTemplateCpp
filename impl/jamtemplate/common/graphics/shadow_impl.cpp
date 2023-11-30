#include "shadow_impl.hpp"

void jt::ShadowImpl::doSetShadow(jt::Color const& col, jt::Vector2f const& offset)
{
    m_shadowActive = true;
    m_shadowColor = col;
    m_shadowOffset = offset;
}

void jt::ShadowImpl::drawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }
    if (m_shadowActive) {
        doDrawShadow(sptr);
    }
}

void jt::ShadowImpl::doSetShadowActive(bool active) { m_shadowActive = active; }

bool jt::ShadowImpl::doGetShadowActive() const { return m_shadowActive; }

jt::Color jt::ShadowImpl::doGetShadowColor() const { return m_shadowColor; }

jt::Vector2f jt::ShadowImpl::doGetShadowOffset() const { return m_shadowOffset; }
