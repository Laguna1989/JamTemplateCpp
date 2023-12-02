#include "outline_impl.hpp"

void jt::OutlineImpl::doSetOutline(Color const& col, int width)
{
    m_outlineActive = width != 0;
    m_outlineColor = col;
    m_outlineWidthInPixel = width;

    m_outlineOffsets.clear();
    auto const maxWidth = doGetOutlineWidth();
    for (auto currentWidth = 1; currentWidth != maxWidth + 1; ++currentWidth) {
        for (auto i = -currentWidth; i != currentWidth + 1; ++i) {
            for (auto j = -currentWidth; j != currentWidth + 1; ++j) {
                m_outlineOffsets.emplace_back(
                    jt::Vector2f { static_cast<float>(i), static_cast<float>(j) });
            }
        }
    }
}

void jt::OutlineImpl::drawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }
    if (m_outlineActive) {
        doDrawOutline(sptr);
    }
}

jt::Color jt::OutlineImpl::doGetOutlineColor() const { return m_outlineColor; }

int jt::OutlineImpl::doGetOutlineWidth() const { return m_outlineWidthInPixel; }

std::vector<jt::Vector2f> jt::OutlineImpl::doGetOutlineOffsets() const { return m_outlineOffsets; }
