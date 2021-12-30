#include "gfx_null.hpp"

namespace jt {
namespace null_objects {

GfxNull::GfxNull()
    : m_window { 800, 600, "test" }
{
    m_textureManager = TextureManagerImpl { nullptr };
}

RenderWindowInterface& GfxNull::window() { return m_window; }
CamInterface& GfxNull::camera() { return m_camera; }
std::shared_ptr<RenderTarget> GfxNull::target() { return m_window.createRenderTarget(); }
TextureManagerInterface& GfxNull::textureManager() { return m_textureManager.value(); }
void GfxNull::reset() { m_camera.reset(); }
void GfxNull::update(float elapsed) { m_camera.update(elapsed); }
void GfxNull::clear() { }
void GfxNull::display() { }

} // namespace null_objects
} // namespace jt
