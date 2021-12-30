#ifndef GUARD_JAMTEMPLATE_GFX_IMPL_HPP
#define GUARD_JAMTEMPLATE_GFX_IMPL_HPP

#include "camera.hpp"
#include "gfx_interface.hpp"
#include "render_window.hpp"
#include "texture_manager_impl.hpp"
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
    std::shared_ptr<sf::View> m_view { nullptr };
    std::unique_ptr<jt::Sprite> m_sprite_for_drawing;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_GFX_IMPL_HPP
