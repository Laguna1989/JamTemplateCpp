#include "gfx_impl.hpp"
#include <utility>

namespace jt {

GfxImpl::GfxImpl(RenderWindow&& window, Camera&& cam)
    : m_window { std::move(window) }
    , m_camera { std::move(cam) }
    , m_renderTarget { m_window.createRenderTarget() }
    , m_textureManager { m_renderTarget }
{
    auto const width = m_window.getSize().x;
    auto const height = m_window.getSize().y;

    auto const scaledWidth = static_cast<int>(width / m_camera.getZoom());
    auto const scaledHeight = static_cast<int>(height / m_camera.getZoom());
    m_srcRect = jt::Recti { 0, 0, scaledWidth, scaledHeight };
    m_destRect = jt::Recti { 0, 0, static_cast<int>(width), static_cast<int>(height) };
}

RenderWindowInterface& GfxImpl::window() { return m_window; }

CamInterface& GfxImpl::camera() { return m_camera; }

std::shared_ptr<RenderTarget> GfxImpl::target() { return m_renderTarget; }

TextureManagerInterface& GfxImpl::textureManager() { return m_textureManager.value(); }

void GfxImpl::reset() { m_camera.reset(); }

void GfxImpl::update(float elapsed)
{
    m_camera.update(elapsed);
    DrawableImpl::setCamOffset(-1.0f * m_camera.getCamOffset());
}

void GfxImpl::clear()
{
    tmpTarget = m_renderTarget.get();
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    t = SDL_CreateTexture(tmpTarget, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        static_cast<int>(m_srcRect.width), static_cast<int>(m_srcRect.height));

    // render to the small texture first
    SDL_SetRenderTarget(tmpTarget, t);
    SDL_RenderClear(tmpTarget);
}

void GfxImpl::display()
{
    // Detach the texture
    SDL_SetRenderTarget(tmpTarget, nullptr);

    // Now render the texture target to our screen
    SDL_RenderClear(tmpTarget);
    SDL_Rect sourceRect { m_srcRect.left, m_srcRect.top, m_srcRect.width, m_srcRect.height };
    SDL_Rect destRect { static_cast<int>(m_camera.getShakeOffset().x),
        static_cast<int>(m_camera.getShakeOffset().y), m_destRect.width, m_destRect.height };
    SDL_RenderCopyEx(tmpTarget, t, &sourceRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
    m_window.display();
    SDL_RenderPresent(tmpTarget);

    SDL_DestroyTexture(t);
}

} // namespace jt
