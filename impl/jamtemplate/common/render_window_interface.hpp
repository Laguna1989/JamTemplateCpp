#ifndef GUARD_JAMTEMPLATE_RENDERWINDOW_INTERFACE_GUARD_HPP
#define GUARD_JAMTEMPLATE_RENDERWINDOW_INTERFACE_GUARD_HPP

#include "render_target.hpp"
#include "sprite.hpp"
#include "vector.hpp"
#include <memory>
#include <string>

namespace jt {

class RenderWindowInterface {
public:
    /// Destructor
    virtual ~RenderWindowInterface() = default;

    /// Check if window is open
    /// \return true if window is open, false otherwise
    virtual bool isOpen() const = 0;

    /// Check if window was closed
    virtual void checkForClose() = 0;

    /// Create the renderTarget to render to
    /// \return shared pointer to render target
    virtual std::shared_ptr<jt::renderTarget> createRenderTarget() = 0;

    /// Get the size of the window
    /// \return
    virtual jt::Vector2 getSize() const = 0;

    /// Draw a sprite to the window
    /// \param sprite the sprite to be drawn
    virtual void draw(std::unique_ptr<jt::Sprite>& sprite) = 0;

    /// Display the current frame
    virtual void display() = 0;

    /// Get the mouse position
    /// \return the mouse position
    virtual jt::Vector2 getMousePosition() = 0;

    /// Set the mouse cursor visible state
    /// \param visible
    virtual void setMouseCursorVisible(bool visible) = 0;

    /// Get the mouse cursor visible state
    /// \return
    virtual bool getMouseCursorVisible() const = 0;
};
} // namespace jt
#endif
