#include "gfx_impl.hpp"
#include <utility>

namespace jt {

GfxImpl::GfxImpl(RenderWindow&& window, Camera&& cam)
    : m_window { std::move(window) }
    , m_camera { std::move(cam) }
{
    m_renderTarget = m_window.createRenderTarget();
    if (m_renderTarget == nullptr) {
        m_textureManager = jt::TextureManagerImpl { nullptr };
        return;
    }
    m_textureManager = jt::TextureManagerImpl { m_renderTarget };

    auto const windowSize = m_window.getSize();
    auto const zoom = m_camera.getZoom();
    auto const scaledWidth = static_cast<unsigned int>(windowSize.x / zoom);
    auto const scaledHeight = static_cast<unsigned int>(windowSize.y / zoom);

    m_renderTarget->create(scaledWidth, scaledHeight);
    m_renderTarget->setSmooth(false);
}

RenderWindowInterface& GfxImpl::window() { return m_window; }

CamInterface& GfxImpl::camera() { return m_camera; }

std::shared_ptr<RenderTarget> GfxImpl::target() { return m_renderTarget; }

TextureManagerInterface& GfxImpl::textureManager() { return m_textureManager.value(); }

} // namespace jt
