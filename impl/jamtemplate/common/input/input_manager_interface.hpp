#ifndef GUARD_JAMTEMPLATE_INPUTMANAGERINTERFACE_HPP
#define GUARD_JAMTEMPLATE_INPUTMANAGERINTERFACE_HPP

#include "control_command_interface.hpp"
#include "key_codes.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {

struct MousePosition {
    float window_x { 0.0f };
    float window_y { 0.0f };

    float screen_x { 0.0f };
    float screen_y { 0.0f };
};

class MouseInputInterface {
public:
    /// Destructor
    virtual ~MouseInputInterface() = default;

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

class KeyboardInputInterface {
public:
    virtual ~KeyboardInputInterface() = default;

    /// Updathe the Keyboard State
    virtual void updateKeys() = 0;

    /// Check if a key is pressed
    /// \param k the key
    /// \return true if pressed, false otherwise
    virtual bool pressed(jt::KeyCode k) = 0;

    /// Check if a key is released
    /// \param k the key
    /// \return true if released, false otherwise
    virtual bool released(jt::KeyCode k) = 0;

    /// Check if a key is just pressed
    /// \param k the key
    /// \return true if just pressed, false otherwise
    virtual bool justPressed(jt::KeyCode k) = 0;

    /// Check if a key is just released
    /// \param k the key
    /// \return true if just released, false otherwise
    virtual bool justReleased(jt::KeyCode k) = 0;

    virtual void reset() = 0;

    virtual void setCommandJustPressed(
        std::vector<KeyCode> const& key, std::shared_ptr<jt::ControlCommandInterface> command)
        = 0;
    virtual void setCommandPressed(
        std::vector<KeyCode> const& key, std::shared_ptr<jt::ControlCommandInterface> command)
        = 0;
    virtual void setCommandReleased(
        std::vector<KeyCode> const& key, std::shared_ptr<jt::ControlCommandInterface> command)
        = 0;
    virtual void setCommandJustReleased(
        std::vector<KeyCode> const& key, std::shared_ptr<jt::ControlCommandInterface> command)
        = 0;
    virtual void updateCommands(float elapsed) = 0;
};

class InputManagerInterface {
public:
    /// Destructor
    virtual ~InputManagerInterface() = default;

    /// Get the mouse input
    /// \return the mouse input (can be nullptr)
    virtual std::shared_ptr<MouseInputInterface> mouse() = 0;

    /// Get the keyboard input
    /// \return the keyboard input (can be nullptr)
    virtual std::shared_ptr<KeyboardInputInterface> keyboard() = 0;

    /// Update the input
    /// \param mp the mouse buttons
    virtual void update(MousePosition const& mp, float elapsed) = 0;

    /// Reset the input
    virtual void reset() = 0;
};

} // namespace jt
#endif
