#ifndef JAMTEMPLATE_KEYBOARD_INTERFACE_HPP
#define JAMTEMPLATE_KEYBOARD_INTERFACE_HPP

#include <input/control_commands/control_command_interface.hpp>
#include <input/keyboard/keyboard_defines.hpp>
#include <memory>

namespace jt {

class KeyboardInterface {
public:
    /// Update the Keyboard State
    virtual void updateKeys() = 0;

    /// Check if a key is pressed
    /// \param k key
    /// \return true if pressed, false otherwise
    virtual bool pressed(jt::KeyCode k) = 0;

    /// Check if a key is released
    /// \param k key
    /// \return true if released, false otherwise
    virtual bool released(jt::KeyCode k) = 0;

    /// Check if a key is just pressed
    /// \param k key
    /// \return true if just pressed, false otherwise
    virtual bool justPressed(jt::KeyCode k) = 0;

    /// Check if a key is just released
    /// \param k key
    /// \return true if just released, false otherwise
    virtual bool justReleased(jt::KeyCode k) = 0;

    /// reset the keyboard input (usually called on state changes)
    virtual void reset() = 0;

    /// Set a control command when a key was just pressed
    /// \param key key to be pressed
    /// \param command command to be executed on key press
    virtual void setCommandJustPressed(
        std::vector<KeyCode> const& key, std::shared_ptr<jt::ControlCommandInterface> command)
        = 0;

    /// Set a control command when a key was pressed
    /// \param key key to be pressed
    /// \param command command to be executed on key press
    virtual void setCommandPressed(
        std::vector<KeyCode> const& key, std::shared_ptr<jt::ControlCommandInterface> command)
        = 0;

    /// Set a control command when a key was released
    /// \param key key to be pressed
    /// \param command command to be executed on key release
    virtual void setCommandReleased(
        std::vector<KeyCode> const& key, std::shared_ptr<jt::ControlCommandInterface> command)
        = 0;

    /// Set a control command when a key was just released
    /// \param key key to be pressed
    /// \param command command to be executed on key release
    virtual void setCommandJustReleased(
        std::vector<KeyCode> const& key, std::shared_ptr<jt::ControlCommandInterface> command)
        = 0;

    /// Update commands
    /// \param elapsed
    virtual void updateCommands(float elapsed) = 0;

    virtual ~KeyboardInterface() = default;

    // no copy, no move. Avoid slicing.
    KeyboardInterface(KeyboardInterface const&) = delete;
    KeyboardInterface(KeyboardInterface&&) = delete;
    KeyboardInterface& operator=(KeyboardInterface const&) = delete;
    KeyboardInterface& operator=(KeyboardInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    KeyboardInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_KEYBOARD_INTERFACE_HPP
