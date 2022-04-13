#ifndef JAMTEMPLATE_GFX_IMPL_HPP
#define JAMTEMPLATE_GFX_IMPL_HPP

#include <cam_interface.hpp>
#include <graphics/gfx_interface.hpp>
#include <graphics/render_window_interface.hpp>
#include <render_target_lib.hpp>
#include <texture_manager_impl.hpp>
#include <SDL2/SDL.h>
#include <optional>

namespace jt {

class GfxImpl : public GfxInterface {
public:
    GfxImpl(RenderWindowInterface& window, CamInterface& cam);
    RenderWindowInterface& window() override;
    CamInterface& camera() override;
    std::shared_ptr<RenderTarget> target() override;
    TextureManagerInterface& textureManager() override;
    void reset() override;
    void update(float elapsed) override;
    void clear() override;
    void display() override;

private:
    RenderWindowInterface& m_window;
    CamInterface& m_camera;
    std::shared_ptr<RenderTarget> m_renderTarget { nullptr };
    std::optional<jt::TextureManagerImpl> m_textureManager;
    RenderTarget* tmpTarget;
    SDL_Texture* t;

    jt::Recti m_srcRect;
    jt::Recti m_destRect;
};

} // namespace jt

#endif // JAMTEMPLATE_GFX_IMPL_HPP
