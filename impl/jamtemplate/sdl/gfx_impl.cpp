#include "gfx_impl.hpp"
#include <render_target_container.hpp>
#include <utility>

namespace jt {

GfxImpl::GfxImpl(RenderWindowInterface& window, CamInterface& cam)
    : m_window { window }
    , m_camera { cam }
{
    // TODO
    m_targets = std::make_shared<jt::RenderTargetContainer>();
    m_targets->m_targets[0] = m_window.createRenderTarget();

    m_textureManager = TextureManagerImpl { m_targets->m_targets[0] };

    auto const width = m_window.getSize().x;
    auto const height = m_window.getSize().y;

    auto const scaledWidth = static_cast<int>(width / m_camera.getZoom());
    auto const scaledHeight = static_cast<int>(height / m_camera.getZoom());
    m_srcRect = jt::Recti { 0, 0, scaledWidth, scaledHeight };
    m_destRect = jt::Recti { 0, 0, static_cast<int>(width), static_cast<int>(height) };
}

RenderWindowInterface& GfxImpl::window() { return m_window; }

CamInterface& GfxImpl::camera() { return m_camera; }

std::shared_ptr<jt::RenderTargetContainerInterface> GfxImpl::target() { return m_targets; }

TextureManagerInterface& GfxImpl::textureManager() { return m_textureManager.value(); }

void GfxImpl::reset() { m_camera.reset(); }

void GfxImpl::update(float elapsed)
{
    m_camera.update(elapsed);
    DrawableImpl::setCamOffset(-1.0f * m_camera.getCamOffset());
}

void GfxImpl::clear()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    m_tmpTexture = SDL_CreateTexture(m_targets->m_targets[0].get(), SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, static_cast<int>(m_srcRect.width),
        static_cast<int>(m_srcRect.height));

    // render to the small texture first
    SDL_SetRenderTarget(m_targets->m_targets[0].get(), m_tmpTexture);
    SDL_RenderClear(m_targets->m_targets[0].get());
}

void GfxImpl::display()
{
    // Detach the texture
    SDL_SetRenderTarget(m_targets->m_targets[0].get(), nullptr);

    // Now render the texture target to our screen
    SDL_RenderClear(m_targets->m_targets[0].get());
    SDL_Rect sourceRect { m_srcRect.left, m_srcRect.top, m_srcRect.width, m_srcRect.height };
    SDL_Rect destRect { static_cast<int>(m_camera.getShakeOffset().x),
        static_cast<int>(m_camera.getShakeOffset().y), m_destRect.width, m_destRect.height };
    SDL_RenderCopyEx(m_targets->m_targets[0].get(), m_tmpTexture, &sourceRect, &destRect, 0,
        nullptr, SDL_FLIP_NONE);
    m_window.display();
    SDL_RenderPresent(m_targets->m_targets[0].get());

    SDL_DestroyTexture(m_tmpTexture);
}

void GfxImpl::createTargetForZ(int z) { }

} // namespace jt
