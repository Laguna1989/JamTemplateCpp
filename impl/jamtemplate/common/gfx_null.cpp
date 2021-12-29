//
// Created by Laguna_HP on 29.12.2021.
//

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

} // namespace null_objects
} // namespace jt
