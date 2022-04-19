#ifndef JAMTEMPLATE_MOUSE_INTERFACE_HPP
#define JAMTEMPLATE_MOUSE_INTERFACE_HPP

#include <input/mouse/mouse_defines.hpp>
#include <vector.hpp>

namespace jt {

class MouseInterface {
public:
    /// Destructor
    virtual ~MouseInterface() = default;

    /// Update the mouse position
    /// \param mousePosition the new mouse position
    virtual void updateMousePosition(MousePosition const& mousePosition) = 0;

    /// Update the mouse button states
    virtual void updateButtons() = 0;

    /// Get the mouse position in the world
    /// \return the mouse position
    virtual jt::Vector2f getMousePositionWorld() = 0;

    /// Get the mouse on the screen
    /// \return the mouse position
    virtual jt::Vector2f getMousePositionScreen() = 0;

    /// Check if a button is pressed
    /// \param b the button
    /// \return true if pressed, false otherwise
    virtual bool pressed(jt::MouseButtonCode b) = 0;

    /// Check if a button is released
    /// \param b the button
    /// \return true if released, false otherwise
    virtual bool released(jt::MouseButtonCode b) = 0;

    /// Check if a button is just pressed
    /// \param b the button
    /// \return true if just released, false otherwise
    virtual bool justPressed(jt::MouseButtonCode b) = 0;

    /// Check if a button is just released
    /// \param b the button
    /// \return true if just released, false otherwise
    virtual bool justReleased(jt::MouseButtonCode b) = 0;

    /// Reset the MouseInput
    virtual void reset() = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_MOUSE_INTERFACE_HPP
