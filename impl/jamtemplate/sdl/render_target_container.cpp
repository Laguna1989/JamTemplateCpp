#include "render_target_container.hpp"

void jt::RenderTargetContainer::forall(std::function<void(std::shared_ptr<jt::RenderTarget>)> func)
{
//    for (auto& kvp : m_textures) {
//        func(kvp.second);
//    }
}

std::shared_ptr<jt::RenderTarget> jt::RenderTargetContainer::get(int z) {
    // TODO check if texture is available
    SDL_SetRenderTarget(m_target.get(), m_textures[z]);
    return m_target;
}

void jt::RenderTargetContainer::add(int z, std::shared_ptr<jt::RenderTarget> target)
{
    if (!m_target)
    {
        m_target = target;
    }
    // TODO create texture for this layer
}
