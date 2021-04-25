#include "KeyboardInput.hpp"
#include "InputHelper.hpp"

namespace jt {

KeyboardInput::KeyboardInput(KeyboardKeyCheckFunction checkFunc)
{
    m_checkFunc = checkFunc;
    auto const allKeys = jt::getAllKeys();
    for (auto const k : allKeys) {
        m_released[k] = false;
    }

    reset();
}

void KeyboardInput::updateKeys()
{
    jt::inputhelper::updateValues(m_pressed, m_released, m_justPressed, m_justReleased,
        [this](auto k) { return m_checkFunc(k); });
}

bool KeyboardInput::pressed(jt::KeyCode k) { return m_pressed[k]; }
bool KeyboardInput::released(jt::KeyCode k) { return m_released[k]; }
bool KeyboardInput::justPressed(jt::KeyCode k) { return m_justPressed[k]; }
bool KeyboardInput::justReleased(jt::KeyCode k) { return m_justReleased[k]; }

void KeyboardInput::reset()
{
    for (auto& kvp : m_released) {
        m_pressed[kvp.first] = false;
        m_released[kvp.first] = false;
        m_justPressed[kvp.first] = false;
        m_justReleased[kvp.first] = false;
    }
}
} // namespace jt
