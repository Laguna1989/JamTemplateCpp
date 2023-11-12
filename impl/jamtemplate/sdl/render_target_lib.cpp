#include "render_target_lib.hpp"
#include <stdexcept>

jt::RenderTarget::RenderTarget(std::shared_ptr<jt::RenderTargetLayer> renderer)
    : m_renderer { renderer }
{
    if (!m_renderer) {
        throw std::invalid_argument { "RenderTarget created with nullptr argument" };
    }
}

std::shared_ptr<jt::RenderTargetLayer> jt::RenderTarget::get(int z)
{
    SDL_SetRenderTarget(m_renderer.get(), m_textures[z].get());
    return m_renderer;
}

void jt::RenderTarget::add(int z, std::shared_ptr<SDL_Texture> texture) { m_textures[z] = texture; }

void jt::RenderTarget::clearPixels()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // render to the small texture first
    bool first { true };
    for (auto& kvp : m_textures) {
        SDL_SetRenderTarget(m_renderer.get(), kvp.second.get());
        if (first) {
            SDL_SetTextureAlphaMod(kvp.second.get(), 255);
            // SDL does not like drawing to a complete transparent background, so the lowest z layer
            // needs to be filled with alpha = 255.
            SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
            SDL_RenderClear(m_renderer.get());
            first = false;
        } else {
            // The "upper" z layers need to be cleared transparently (alpha = 0) otherwise the
            // layers below are not visible.
            SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 0);
            SDL_RenderClear(m_renderer.get());
        }
    }
}
