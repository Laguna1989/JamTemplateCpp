#ifndef JAMTEMPLATE_GAMEPAD_INPUT_HPP
#define JAMTEMPLATE_GAMEPAD_INPUT_HPP

#include <gamepad_input_lib.hpp>
#include <input/gamepad/gamepad_interface.hpp>
#include <functional>
#include <map>

namespace jt {

class GamepadInput : public jt::GamepadInterface {
public:
    using AxisFunc = std::function<jt::Vector2f(jt::GamepadAxisCode)>;
    using ButtonCheckFunction = std::function<bool(jt::GamepadButtonCode)>;

    explicit GamepadInput(
        int gamepadId, AxisFunc axisFunc = nullptr, ButtonCheckFunction buttonFunc = nullptr);
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

#endif // JAMTEMPLATE_GAMEPAD_INPUT_HPP
