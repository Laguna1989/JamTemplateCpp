#ifndef JAMTEMPLATE_RENDER_TARGET_LIB_HPP
#define JAMTEMPLATE_RENDER_TARGET_LIB_HPP

#include <graphics/render_target_interface.hpp>
#include <sdl_2_include.hpp>
#include <memory>

namespace jt {

class RenderTarget : public RenderTargetInterface {
public:
    explicit RenderTarget(std::shared_ptr<jt::RenderTargetLayer> renderer = nullptr);
    std::shared_ptr<jt::RenderTargetLayer> get(int z) override;

    void add(int z, std::shared_ptr<SDL_Texture> texture);

    void clearPixels();

    std::shared_ptr<SDL_Renderer> m_renderer { nullptr };

    std::map<int, std::shared_ptr<SDL_Texture>> m_textures;
};
} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_LIB_HPP
