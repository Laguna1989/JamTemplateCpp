#include "render_target_container.hpp"
#include <stdexcept>

jt::RenderTargetContainer::RenderTargetContainer(std::shared_ptr<jt::RenderTarget> target)
    : m_target { target }
{
    if (!m_target) {
        throw std::invalid_argument { "RenderTargetContainer created with nullptr argument" };
    }
}

std::shared_ptr<jt::RenderTarget> jt::RenderTargetContainer::get(int z)
{
    SDL_SetRenderTarget(m_target.get(), m_textures[z].get());
    return m_target;
}

void jt::RenderTargetContainer::add(int z, std::shared_ptr<SDL_Texture> texture)
{
    m_textures[z] = texture;
}

void jt::RenderTargetContainer::clear()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // render to the small texture first
    bool first { true };
    for (auto& kvp : m_textures) {
        SDL_SetRenderTarget(m_target.get(), kvp.second.get());
        if (first) {
            SDL_SetTextureAlphaMod(kvp.second.get(), 255);
            SDL_SetRenderDrawColor(m_target.get(), 0, 0, 0, 255);
            SDL_RenderClear(m_target.get());
            first = false;
        } else {
            SDL_SetRenderDrawColor(m_target.get(), 0, 0, 0, 0);
            SDL_RenderClear(m_target.get());
        }
    }
}
