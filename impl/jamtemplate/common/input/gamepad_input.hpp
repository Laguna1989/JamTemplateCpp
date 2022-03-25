#ifndef MYAWESOMEGAME_GAMEPAD_INPUT_HPP
#define MYAWESOMEGAME_GAMEPAD_INPUT_HPP

#include "gamepad_input_lib.hpp"
#include "input_manager_interface.hpp"
#include <functional>

namespace jt {

class GamepadInput : public jt::GamepadInputInterface {
public:
    using AxisFunc = std::function<jt::Vector2f(jt::GamepadAxisCode)>;

    GamepadInput(AxisFunc axisFunc = [](auto k) { return libAxisValue(k); });
    void update() override;
    jt::Vector2f getAxisRaw(jt::GamepadAxisCode axis) override;
    Vector2f getAxis(jt::GamepadAxisCode axis) override;
    void reset() override;

private:
    AxisFunc m_axisFunc;

    float m_axisDeadZone { 11.0f };
};

} // namespace jt

#endif // MYAWESOMEGAME_GAMEPAD_INPUT_HPP
