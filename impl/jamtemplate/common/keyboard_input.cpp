#include "keyboard_input.hpp"
#include "control_command_null.hpp"
#include "input_helper.hpp"

namespace jt {

KeyboardInput::KeyboardInput(KeyboardKeyCheckFunction checkFunc)
    : m_checkFunc { std::move(checkFunc) }
{
    // note: do not call the virtual reset() function here, as this is the constructor
    for (auto const k : jt::getAllKeys()) {
        m_pressed[k] = false;
        m_released[k] = false;
        m_justPressed[k] = false;
        m_justReleased[k] = false;

        m_commandsJustPressed[k] = std::make_shared<ControlCommandNull>();
    }
}

void KeyboardInput::updateKeys()
{
    jt::inputhelper::updateValues(m_pressed, m_released, m_justPressed, m_justReleased,
        [this](auto k) { return m_checkFunc(k); });

    for (auto const k : jt::getAllKeys()) {
        if (justPressed(k)) {
            m_commandsJustPressed[k]->execute();
        }
    }
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

        // TODO
        //        m_commands[kvp.first] = std::make_shared<ControlCommandNull>();
    }
}

void KeyboardInput::setCommandJustPressed(
    jt::KeyCode key, std::shared_ptr<jt::ControlCommandInterface> command)
{
    //    m_command = command;
    m_commandsJustPressed[key] = command;
}
} // namespace jt
