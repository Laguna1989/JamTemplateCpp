#include "gfx_impl.hpp"
#include <render_target_lib.hpp>

namespace jt {

GfxImpl::GfxImpl(RenderWindowInterface& window, CamInterface& cam)
    : m_window { window }
    , m_camera { cam }
{
    m_target = std::make_shared<jt::RenderTarget>(m_window.createRenderTarget());

    auto const width = m_window.getSize().x;
    auto const height = m_window.getSize().y;

    auto const scaledWidth = static_cast<int>(width / m_camera.getZoom());
    auto const scaledHeight = static_cast<int>(height / m_camera.getZoom());
    m_srcRect = jt::Recti { 0, 0, scaledWidth, scaledHeight };
    m_destRect = jt::Recti { 0, 0, static_cast<int>(width), static_cast<int>(height) };

    GfxImpl::createZLayer(0);

    m_textureManager = TextureManagerImpl { m_target->get(0) };
}

RenderWindowInterface& GfxImpl::window() { return m_window; }

CamInterface& GfxImpl::camera() { return m_camera; }

std::shared_ptr<jt::RenderTargetInterface> GfxImpl::target() { return m_target; }

TextureManagerInterface& GfxImpl::textureManager() { return m_textureManager.value(); }

void GfxImpl::reset() { m_camera.reset(); }

void GfxImpl::update(float elapsed)
{
    m_camera.update(elapsed);
    DrawableImpl::setCamOffset(-1.0f * m_camera.getCamOffset());
}

void GfxImpl::clear() { m_target->clearPixels(); }

void GfxImpl::display()
{
    // Detach the texture
    SDL_SetRenderTarget(m_target->m_renderer.get(), nullptr);
    SDL_RenderClear(m_target->m_renderer.get());

    for (auto& kvp : m_target->m_textures) {
        // Now render the textures to our screen

        SDL_Rect sourceRect { m_srcRect.left, m_srcRect.top, m_srcRect.width, m_srcRect.height };
        SDL_Rect destRect { static_cast<int>(m_camera.getShakeOffset().x),
            static_cast<int>(m_camera.getShakeOffset().y), m_destRect.width, m_destRect.height };
        SDL_RenderCopyEx(m_target->m_renderer.get(), kvp.second.get(), &sourceRect, &destRect, 0,
            nullptr, SDL_FLIP_NONE);
        m_window.display();
        SDL_RenderPresent(m_target->m_renderer.get());
    }
}

void GfxImpl::createZLayer(int z)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    auto const texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTexture(m_target->m_renderer.get(), SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, static_cast<int>(m_srcRect.width),
            static_cast<int>(m_srcRect.height)),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
    SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
    m_target->add(z, texture);
}

} // namespace jt
