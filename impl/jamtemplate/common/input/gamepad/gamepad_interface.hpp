#ifndef JAMTEMPLATE_GAMEPAD_INTERFACE_HPP
#define JAMTEMPLATE_GAMEPAD_INTERFACE_HPP

#include <input/gamepad/gamepad_defines.hpp>
#include <vector.hpp>

namespace jt {

class GamepadInterface {
public:
    /// Update the gamepad button states
    virtual void update() = 0;

    /// Check if a Gamepad key is pressed
    /// \param b the key
    /// \return true if pressed, false otherwise
    virtual bool pressed(GamepadButtonCode b) = 0;

    /// Check if a key is released
    /// \param b the key
    /// \return true if released, false otherwise
    virtual bool released(GamepadButtonCode b) = 0;

    /// Check if a key is just pressed
    /// \param b the key
    /// \return true if just pressed, false otherwise
    virtual bool justPressed(GamepadButtonCode b) = 0;

    /// Check if a key is just released
    /// \param b the key
    /// \return true if just released, false otherwise
    virtual bool justReleased(GamepadButtonCode b) = 0;

    /// Get the raw axis position value
    /// \return the axis position
    virtual Vector2f getAxisRaw(jt::GamepadAxisCode axis) = 0;

    /// Get the axis position value
    /// \param axis
    /// \return the axis position with range [-1, 1]
    virtual Vector2f getAxis(jt::GamepadAxisCode axis) = 0;

    /// Reset the Gamepad Input
    virtual void reset() = 0;

    virtual ~GamepadInterface() = default;

    // no copy, no move. Avoid slicing.
    GamepadInterface(GamepadInterface const&) = delete;
    GamepadInterface(GamepadInterface&&) = delete;
    GamepadInterface& operator=(GamepadInterface const&) = delete;
    GamepadInterface& operator=(GamepadInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    GamepadInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_GAMEPAD_INTERFACE_HPP
