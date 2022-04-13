#ifndef JAMTEMPLATE_GFX_IMPL_HPP
#define JAMTEMPLATE_GFX_IMPL_HPP

#include <camera.hpp>
#include <graphics/gfx_interface.hpp>
#include <graphics/render_window.hpp>
#include <texture_manager_impl.hpp>
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
    std::shared_ptr<sf::View> m_view { nullptr };
    std::unique_ptr<jt::Sprite> m_sprite_for_drawing;
};

} // namespace jt

#endif // JAMTEMPLATE_GFX_IMPL_HPP
