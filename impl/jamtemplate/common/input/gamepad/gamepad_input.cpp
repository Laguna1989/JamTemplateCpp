#include "gamepad_input.hpp"
#include "performance_measurement.hpp"
#include <input/input_helper.hpp>
#include <tracy/Tracy.hpp>

jt::GamepadInput::GamepadInput(int gamepadId, AxisFunc axisFunc, ButtonCheckFunction buttonFunc)
    : m_axisFunc { axisFunc }
{
    if (m_axisFunc == nullptr) {
        m_axisFunc = [gamepadId](auto k) { return libAxisValue(gamepadId, k); };
    }
    m_buttonFunc = buttonFunc;
    if (m_buttonFunc == nullptr) {
        m_buttonFunc = [gamepadId](auto b) { return libGPButtonValue(gamepadId, b); };
    }
    // note: do not call the virtual reset() function here, as this is the constructor
    for (auto const k : jt::getAllGamepadButtons()) {
        m_pressed[k] = false;
        m_released[k] = false;
        m_justPressed[k] = false;
        m_justReleased[k] = false;
    }
}

void jt::GamepadInput::update()
{
    ZoneScopedN("jt::GamepadInput::update");
    jt::inputhelper::updateValues(m_pressed, m_released, m_justPressed, m_justReleased,
        [this](auto k) { return m_buttonFunc(k); });
}

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

bool jt::GamepadInput::pressed(GamepadButtonCode b) { return m_pressed[b]; }

bool jt::GamepadInput::released(GamepadButtonCode b) { return m_released[b]; }

bool jt::GamepadInput::justPressed(GamepadButtonCode b) { return m_justPressed[b]; }

bool jt::GamepadInput::justReleased(GamepadButtonCode b) { return m_justReleased[b]; }
