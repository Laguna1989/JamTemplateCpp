#include "drawable_flash_impl.hpp"
#include "linterp.hpp"

namespace jt {

void DrawableFlashImpl::drawFlash(std::shared_ptr<jt::RenderTarget> sptr) const
{
    if (sptr) {
        if (m_flashTimer >= 0) {
            doDrawFlash(sptr);
        }
    }
}

void DrawableFlashImpl::doFlash(float t, jt::Color col)
{
    m_flashTimer = t;
    m_maxFlashTimer = t;
    m_flashColor = col;

    doFlashImpl(t, col);
}

void DrawableFlashImpl::doSetFlashColor(Color const& col) { m_flashColor = col; }
jt::Color DrawableFlashImpl::doGetFlashColor() const { return m_flashColor; }

void DrawableFlashImpl::updateFlash(float elapsed)
{
    if (m_flashTimer > 0) {
        m_flashTimer -= elapsed;
        auto col = doGetFlashColor();
        float const a = Lerp::linear(
            static_cast<float>(col.a), 0.0f, 1.0f - (m_flashTimer / m_maxFlashTimer));
        col.a = static_cast<std::uint8_t>(a);
        doSetFlashColor(col);
    }
}

} // namespace jt
