#ifndef JAMTEMPLATE_INPUTMANAGERINTERFACE_HPP
#define JAMTEMPLATE_INPUTMANAGERINTERFACE_HPP

#include <input/control_commands/control_command_interface.hpp>
#include <input/gamepad/gamepad_interface.hpp>
#include <input/keyboard/keyboard_interface.hpp>
#include <input/mouse/mouse_interface.hpp>
#include <memory>

namespace jt {

class InputManagerInterface {
public:
    /// Destructor
    virtual ~InputManagerInterface() = default;

    /// Get the mouse input
    /// \return the mouse input (can be nullptr)
    virtual std::shared_ptr<MouseInterface> mouse() = 0;

    /// Get the keyboard input
    /// \return the keyboard input (can be nullptr)
    virtual std::shared_ptr<KeyboardInterface> keyboard() = 0;

    /// Get the gamepad input
    /// \return the gamepad
    virtual std::shared_ptr<GamepadInterface> gamepad(int gamepad_id) = 0;

    virtual std::size_t getNumberOfGamepads() const = 0;

    /// Update the input
    /// \param mp the mouse buttons
    virtual void update(MousePosition const& mp, float elapsed) = 0;

    /// Reset the input
    virtual void reset() = 0;
};

} // namespace jt
#endif
