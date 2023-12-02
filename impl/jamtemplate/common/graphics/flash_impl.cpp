#include "flash_impl.hpp"

void jt::FlashImpl::drawFlash(std::shared_ptr<jt::RenderTargetLayer> sptr) const
{
    if (sptr) [[likely]] {
        if (m_flashTimer >= 0) {
            doDrawFlash(sptr);
        }
    }
}

void jt::FlashImpl::doFlash(float t, jt::Color col)
{
    m_flashTimer = t;
    m_maxFlashTimer = t;
    m_flashColor = col;

    doFlashImpl(t, col);
}

void jt::FlashImpl::doSetFlashColor(jt::Color const& col) { m_flashColor = col; }

jt::Color jt::FlashImpl::doGetFlashColor() const { return m_flashColor; }

void jt::FlashImpl::updateFlash(float elapsed)
{
    if (m_flashTimer > 0) {
        auto const a = (m_flashTimer / m_maxFlashTimer);

        auto col = doGetFlashColor();
        col.a = static_cast<std::uint8_t>(a * 255.0f);
        doSetFlashColor(col);

        m_flashTimer -= elapsed;
    }
}
