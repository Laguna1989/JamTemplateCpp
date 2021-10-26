#include "keyboard_input.hpp"
#include "input_helper.hpp"

namespace jt {

KeyboardInput::KeyboardInput(KeyboardKeyCheckFunction checkFunc)
    : m_checkFunc { std::move(checkFunc) }
{
    auto const allKeys = jt::getAllKeys();
    // note: do not call the virtual reset() function here, as this is the constructor
    for (auto const k : allKeys) {
        m_pressed[k] = false;
        m_released[k] = false;
        m_justPressed[k] = false;
        m_justReleased[k] = false;
    }
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
