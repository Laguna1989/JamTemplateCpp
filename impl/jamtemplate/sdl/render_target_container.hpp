#ifndef JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP
#define JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP

#include <graphics/render_target_container_interface.hpp>
#include <SDL2/SDL.h>
#include <memory>

namespace jt {

class RenderTargetContainer : public RenderTargetContainerInterface {
public:
    explicit RenderTargetContainer(std::shared_ptr<jt::RenderTarget> target = nullptr);
    std::shared_ptr<jt::RenderTarget> get(int z) override;

    void add(int z, std::shared_ptr<SDL_Texture> texture);

    void clear();
    std::map<int, std::shared_ptr<SDL_Texture>> m_textures;

    std::shared_ptr<jt::RenderTarget> m_target { nullptr };
};
} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP
