#include "gfx_null.hpp"
#include <render_target_lib.hpp>

jt::null_objects::GfxNull::GfxNull()
    : m_window { 800, 600, "test" }
    , m_textureManager { TextureManagerImpl { nullptr } }
    , m_target { std::make_shared<jt::RenderTarget>() }
{
}

jt::RenderWindowInterface& jt::null_objects::GfxNull::window() { return m_window; }
jt::CamInterface& jt::null_objects::GfxNull::camera() { return m_camera; }
std::shared_ptr<jt::RenderTargetInterface> jt::null_objects::GfxNull::target() { return m_target; }
jt::TextureManagerInterface& jt::null_objects::GfxNull::textureManager()
{
    return m_textureManager.value();
}
void jt::null_objects::GfxNull::reset() { m_camera.reset(); }
void jt::null_objects::GfxNull::update(float elapsed) { m_camera.update(elapsed); }
void jt::null_objects::GfxNull::clear() { }
void jt::null_objects::GfxNull::display() { }

void jt::null_objects::GfxNull::createZLayer(int /*z*/) { }
