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
