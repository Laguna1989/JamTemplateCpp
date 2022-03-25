#include "gamepad_input.hpp"

jt::GamepadInput::GamepadInput(jt::GamepadInput::AxisFunc axisFunc)
    : m_axisFunc { axisFunc }
{
}

void jt::GamepadInput::update() { }

jt::Vector2f jt::GamepadInput::getAxisRaw(jt::GamepadAxisCode axis) { return m_axisFunc(axis); }
jt::Vector2f jt::GamepadInput::getAxis(jt::GamepadAxisCode axis)
{
    auto v = getAxisRaw(axis);
    if (abs(v.x) < m_axisDeadZone) {
        v.x = 0.0f;
    }
    if (abs(v.y) < m_axisDeadZone) {
        v.y = 0.0f;
    }
    return v / 100.0f;
}

void jt::GamepadInput::reset() { }
