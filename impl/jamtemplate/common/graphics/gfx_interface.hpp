#ifndef JAMTEMPLATE_GFX_INTERFACE_HPP
#define JAMTEMPLATE_GFX_INTERFACE_HPP

#include <cam_interface.hpp>
#include <graphics/render_target_interface.hpp>
#include <graphics/render_window_interface.hpp>
#include <texture_manager_interface.hpp>

namespace jt {

class GfxInterface {
public:
    /// Get the render window
    /// \return the render window
    virtual RenderWindowInterface& window() = 0;

    /// Get the camera
    /// \return the camera
    virtual CamInterface& camera() = 0;

    /// Get the render target
    /// \return the render target
    virtual std::shared_ptr<jt::RenderTargetInterface> target() = 0;

    /// Get the texture manager
    /// \return the texture manager
    virtual TextureManagerInterface& textureManager() = 0;

    /// Reset the gfx (e.g. on switchState())
    virtual void reset() = 0;

    /// update the gfx
    /// \param elapsed the elapsed time
    virtual void update(float elapsed) = 0;

    /// clear the gfx
    virtual void clear() = 0;

    /// display the drawables to the screen
    virtual void display() = 0;

    /// Create a ZLayer (to be used with DrawableInterface::setZ())
    /// \param z The z layer. Drawables will be drawn in ascending order, that means z layer 2 is
    /// drawn above z layer 1.
    virtual void createZLayer(int z) = 0;

    virtual ~GfxInterface() = default;

    // no copy, no move. Avoid slicing.
    GfxInterface(GfxInterface const&) = delete;
    GfxInterface(GfxInterface&&) = delete;
    GfxInterface& operator=(GfxInterface const&) = delete;
    GfxInterface& operator=(GfxInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    GfxInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_GFX_INTERFACE_HPP
