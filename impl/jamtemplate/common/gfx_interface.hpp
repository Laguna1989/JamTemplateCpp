#ifndef GUARD_JAMTEMPLATE_GFX_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_GFX_INTERFACE_HPP

#include "cam_interface.hpp"
#include "render_target.hpp"
#include "render_window_interface.hpp"
#include "texture_manager_interface.hpp"

namespace jt {

class GfxInterface {
public:
    virtual ~GfxInterface() = default;
    virtual RenderWindowInterface& window() = 0;
    virtual CamInterface& camera() = 0;
    virtual std::shared_ptr<RenderTarget> target() = 0;
    virtual TextureManagerInterface& textureManager() = 0;

    virtual void reset() = 0;
    virtual void update(float elapsed) = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_GFX_INTERFACE_HPP
