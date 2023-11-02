#ifndef JAMTEMPLATE_SHADOW_IMPL_HPP
#define JAMTEMPLATE_SHADOW_IMPL_HPP

#include <color/color.hpp>
#include <render_target_layer.hpp>
#include <vector.hpp>
#include <memory>

namespace jt {

class ShadowImpl {
public:
    void doSetShadow(jt::Color const& col, jt::Vector2f const& offset);

    void drawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const;

    void doSetShadowActive(bool active);

    bool doGetShadowActive() const;
    jt::Color doGetShadowColor() const;
    jt::Vector2f doGetShadowOffset() const;

private:
    bool m_shadowActive { false };
    jt::Vector2f m_shadowOffset { 0.0f, 0.0f };
    jt::Color m_shadowColor { jt::colors::Black };
    virtual void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_SHADOW_IMPL_HPP
