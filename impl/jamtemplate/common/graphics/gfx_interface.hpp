#ifndef JAMTEMPLATE_GFX_INTERFACE_HPP
#define JAMTEMPLATE_GFX_INTERFACE_HPP

#include <cam_interface.hpp>
#include <graphics/render_window_interface.hpp>
#include <render_target.hpp>
#include <texture_manager_interface.hpp>

namespace jt {

class GfxInterface {
public:
    virtual ~GfxInterface() = default;

    // no copy, no move. Avoid slicing.
    GfxInterface(const GfxInterface&) = delete;
    GfxInterface(GfxInterface&&) = delete;
    GfxInterface& operator=(const GfxInterface&) = delete;
    GfxInterface& operator=(GfxInterface&&) = delete;

    virtual RenderWindowInterface& window() = 0;
    virtual CamInterface& camera() = 0;
    virtual std::shared_ptr<RenderTarget> target() = 0;
    virtual TextureManagerInterface& textureManager() = 0;

    virtual void reset() = 0;
    virtual void update(float elapsed) = 0;
    virtual void clear() = 0;
    virtual void display() = 0;

protected:
    // constructor can only be called from derived classes

    GfxInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_GFX_INTERFACE_HPP
