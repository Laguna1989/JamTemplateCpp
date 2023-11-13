#ifndef JAMTEMPLATE_INPUT_GET_INTERFACE_HPP
#define JAMTEMPLATE_INPUT_GET_INTERFACE_HPP

#include <input/gamepad/gamepad_interface.hpp>
#include <input/keyboard/keyboard_interface.hpp>
#include <input/mouse/mouse_interface.hpp>

namespace jt {

class InputGetInterface {
public:
    /// Get the mouse input
    /// \return the mouse input
    virtual std::shared_ptr<MouseInterface> mouse() = 0;

    /// Get the keyboard input
    /// \return the keyboard input
    virtual std::shared_ptr<jt::KeyboardInterface> keyboard() = 0;

    /// Get the gamepad input
    /// \return the gamepad
    virtual std::shared_ptr<GamepadInterface> gamepad(int gamepad_id) = 0;

    /// Get the number of connected gamepads
    /// \return the number of gamepads
    virtual std::size_t getNumberOfGamepads() const = 0;

    virtual ~InputGetInterface() = default;

    // no copy, no move. Avoid slicing.
    InputGetInterface(InputGetInterface const&) = delete;
    InputGetInterface(InputGetInterface&&) = delete;
    InputGetInterface& operator=(InputGetInterface const&) = delete;
    InputGetInterface& operator=(InputGetInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    InputGetInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_INPUT_GET_INTERFACE_HPP
