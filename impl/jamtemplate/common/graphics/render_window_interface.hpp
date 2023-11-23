#ifndef JAMTEMPLATE_RENDERWINDOW_INTERFACE_HPP
#define JAMTEMPLATE_RENDERWINDOW_INTERFACE_HPP

#include <render_target_layer.hpp>
#include <sprite.hpp>
#include <vector.hpp>
#include <memory>
#include <string>

namespace jt {

class RenderWindowInterface {
public:
    /// Check if window is open
    /// \return true if window is open, false otherwise
    virtual bool isOpen() const = 0;

    /// Check if window was closed
    virtual void checkForClose() = 0;

    /// Create the RenderTargetLayer to render to
    /// \return shared pointer to render target
    virtual std::shared_ptr<jt::RenderTargetLayer> createRenderTarget() = 0;

    /// Get the size of the window
    /// \return
    virtual jt::Vector2f getSize() const = 0;

    /// Draw a sprite to the window
    /// \param sprite the sprite to be drawn
    virtual void draw(std::unique_ptr<jt::Sprite>& sprite) = 0;

    /// Display the current frame
    virtual void display() = 0;

    /// Get the mouse position
    /// \return the mouse position
    virtual jt::Vector2f getMousePosition() = 0;

    /// Set the mouse cursor visible state
    /// \param visible
    virtual void setMouseCursorVisible(bool visible) = 0;

    /// Get the mouse cursor visible state
    /// \return
    virtual bool getMouseCursorVisible() const = 0;

    /// Update GUI
    /// \param elapsed the elapsed time in seconds
    virtual void updateGui(float elapsed) = 0;

    /// start to render the GUI
    virtual void startRenderGui() = 0;

    /// Can be used to check if ImGui is taking the keyboard focus
    /// \return true if game should process keyboard input
    virtual bool shouldProcessKeyboard() = 0;

    /// Can be used to check if ImGui is taking the mouse focus
    /// \return true if the game should process mouse input
    virtual bool shouldProcessMouse() = 0;

    /// Destructor
    virtual ~RenderWindowInterface() = default;

    // no copy, no move. Avoid slicing.
    RenderWindowInterface(RenderWindowInterface const&) = delete;
    RenderWindowInterface(RenderWindowInterface&&) = delete;
    RenderWindowInterface& operator=(RenderWindowInterface const&) = delete;
    RenderWindowInterface& operator=(RenderWindowInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    RenderWindowInterface() = default;
};
} // namespace jt
#endif
