#ifndef JAMTEMPLATE_KEYBOARD_INTERFACE_HPP
#define JAMTEMPLATE_KEYBOARD_INTERFACE_HPP

#include <input/control_commands/control_command_interface.hpp>
#include <input/keyboard/keyboard_defines.hpp>
#include <memory>

namespace jt {

class KeyboardInterface {
public:
    virtual ~KeyboardInterface() = default;

    /// Update the the Keyboard State
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

} // namespace jt

#endif // JAMTEMPLATE_KEYBOARD_INTERFACE_HPP
