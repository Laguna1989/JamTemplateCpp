#ifndef JAMTEMPLATE_GFX_IMPL_HPP
#define JAMTEMPLATE_GFX_IMPL_HPP

#include <camera.hpp>
#include <graphics/gfx_interface.hpp>
#include <graphics/render_window.hpp>
#include <render_target_lib.hpp>
#include <texture_manager_impl.hpp>
#include <optional>

namespace jt {

class GfxImpl : public GfxInterface {
public:
    GfxImpl(RenderWindowInterface& window, CamInterface& cam);
    RenderWindowInterface& window() override;
    CamInterface& camera() override;

    std::shared_ptr<jt::RenderTargetInterface> target() override;
    TextureManagerInterface& textureManager() override;

    void reset() override;
    void update(float elapsed) override;
    void clear() override;
    void display() override;

    void createZLayer(int z) override;

private:
    RenderWindowInterface& m_window;
    CamInterface& m_camera;
    jt::Vector2f m_viewHalfSize { 0.0f, 0.0f };
    std::shared_ptr<jt::RenderTarget> m_target { nullptr };
    std::optional<jt::TextureManagerImpl> m_textureManager {};
    std::shared_ptr<sf::View> m_view { nullptr };

    void drawOneZLayer(std::shared_ptr<jt::RenderTargetLayer> const& layer);
};

} // namespace jt

#endif // JAMTEMPLATE_GFX_IMPL_HPP
