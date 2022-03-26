#ifndef GUARD_JAMTEMPLATE_GAMEPAD_INPUT_HPP
#define GUARD_JAMTEMPLATE_GAMEPAD_INPUT_HPP

#include "gamepad_input_lib.hpp"
#include "input_manager_interface.hpp"
#include <functional>
#include <map>

namespace jt {

class GamepadInput : public jt::GamepadInputInterface {
public:
    using AxisFunc = std::function<jt::Vector2f(jt::GamepadAxisCode)>;
    using ButtonCheckFunction = std::function<bool(jt::GamepadButtonCode)>;

    GamepadInput(
        AxisFunc axisFunc = [](auto k) { return libAxisValue(k); },
        ButtonCheckFunction buttonFunc = [](auto b) { return libGPButtonValue(b); });
    void update() override;
    jt::Vector2f getAxisRaw(jt::GamepadAxisCode axis) override;
    Vector2f getAxis(jt::GamepadAxisCode axis) override;
    void reset() override;

    bool pressed(GamepadButtonCode b) override;
    bool released(GamepadButtonCode b) override;
    bool justPressed(GamepadButtonCode b) override;
    bool justReleased(GamepadButtonCode b) override;

private:
    AxisFunc m_axisFunc;
    ButtonCheckFunction m_buttonFunc;

    std::map<jt::GamepadButtonCode, bool> m_pressed {};
    std::map<jt::GamepadButtonCode, bool> m_released {};
    std::map<jt::GamepadButtonCode, bool> m_justPressed {};
    std::map<jt::GamepadButtonCode, bool> m_justReleased {};

    float m_axisDeadZone { 13.0f };
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_GAMEPAD_INPUT_HPP
