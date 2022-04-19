#ifndef JAMTEMPLATE_GAMEPAD_INPUT_NULL_HPP
#define JAMTEMPLATE_GAMEPAD_INPUT_NULL_HPP

#include <input/gamepad/gamepad_interface.hpp>

namespace jt {

class GamepadInputNull : public GamepadInterface {
public:
    void update() override;
    Vector2f getAxisRaw(jt::GamepadAxisCode axis) override;
    Vector2f getAxis(jt::GamepadAxisCode axis) override;
    bool pressed(GamepadButtonCode b) override;
    bool released(GamepadButtonCode b) override;
    bool justPressed(GamepadButtonCode b) override;
    bool justReleased(GamepadButtonCode b) override;
    void reset() override;
};

} // namespace jt

#endif // JAMTEMPLATE_GAMEPAD_INPUT_NULL_HPP
