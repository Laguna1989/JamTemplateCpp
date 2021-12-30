#ifndef GUARD_JAMTEMPALTE_GFX_NULL_HPP
#define GUARD_JAMTEMPALTE_GFX_NULL_HPP

#include "camera.hpp"
#include "gfx_interface.hpp"
#include "render_window_null.hpp"
#include "texture_manager_impl.hpp"
#include <optional>

namespace jt {
namespace null_objects {

class GfxNull : public GfxInterface {
public:
    GfxNull();
    RenderWindowInterface& window() override;
    CamInterface& camera() override;
    std::shared_ptr<RenderTarget> target() override;
    TextureManagerInterface& textureManager() override;
    void reset() override;
    void update(float elapsed) override;
    void clear() override;
    void display() override;

private:
    RenderWindowNull m_window;
    jt::Camera m_camera;
    std::optional<jt::TextureManagerImpl> m_textureManager;
};

} // namespace null_objects
} // namespace jt

#endif // GUARD_JAMTEMPALTE_GFX_NULL_HPP
