#include "gfx_impl.hpp"
#include <utility>

namespace jt {

GfxImpl::GfxImpl(RenderWindow&& window, Camera&& cam)
    : m_window { std::move(window) }
    , m_camera { std::move(cam) }
    , m_renderTarget { m_window.createRenderTarget() }
    , m_textureManager { m_renderTarget }
{
}

RenderWindowInterface& GfxImpl::window() { return m_window; }

CamInterface& GfxImpl::camera() { return m_camera; }

std::shared_ptr<RenderTarget> GfxImpl::target() { return m_renderTarget; }

TextureManagerInterface& GfxImpl::textureManager() { return m_textureManager.value(); }

void GfxImpl::reset() { m_camera.reset(); }

void GfxImpl::update(float elapsed) { m_camera.update(elapsed); }

void GfxImpl::display() { m_window.display(); }

} // namespace jt
