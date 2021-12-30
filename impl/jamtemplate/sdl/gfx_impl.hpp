#ifndef GUARD_JAMTEMPLATE_GFX_IMPL_HPP
#define GUARD_JAMTEMPLATE_GFX_IMPL_HPP

#include "camera.hpp"
#include "gfx_interface.hpp"
#include "render_target_lib.hpp"
#include "render_window.hpp"
#include "texture_manager_impl.hpp"
#include <SDL2/SDL.h>
#include <optional>

namespace jt {

class GfxImpl : public GfxInterface {
public:
    GfxImpl(RenderWindow&& window, Camera&& cam);
    RenderWindowInterface& window() override;
    CamInterface& camera() override;
    std::shared_ptr<RenderTarget> target() override;
    TextureManagerInterface& textureManager() override;
    void reset() override;
    void update(float elapsed) override;
    void clear() override;
    void display() override;

private:
    RenderWindow m_window;
    Camera m_camera;
    std::shared_ptr<RenderTarget> m_renderTarget { nullptr };
    std::optional<jt::TextureManagerImpl> m_textureManager;
    RenderTarget* tmpTarget;
    SDL_Texture* t;

    jt::Recti m_srcRect;
    jt::Recti m_destRect;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_GFX_IMPL_HPP
