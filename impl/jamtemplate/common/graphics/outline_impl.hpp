#ifndef JAMTEMPLATE_OUTLINE_IMPL_HPP
#define JAMTEMPLATE_OUTLINE_IMPL_HPP

#include <color/color.hpp>
#include <render_target_layer.hpp>
#include <vector.hpp>
#include <memory>
#include <vector>

namespace jt {

class OutlineImpl {
public:
    void doSetOutline(jt::Color const& col, int width);

    void drawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const;

    jt::Color doGetOutlineColor() const;
    int doGetOutlineWidth() const;

    std::vector<jt::Vector2f> doGetOutlineOffsets() const;

private:
    bool m_outlineActive { false };
    int m_outlineWidthInPixel { 0 };
    jt::Color m_outlineColor { jt::colors::Black };

    std::vector<jt::Vector2f> m_outlineOffsets {};

    virtual void doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_OUTLINE_IMPL_HPP
