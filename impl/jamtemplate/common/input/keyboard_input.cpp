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

        m_commandsPressed[k] = std::make_shared<ControlCommandNull>();
        m_commandsReleased[k] = std::make_shared<ControlCommandNull>();
        m_commandsJustPressed[k] = std::make_shared<ControlCommandNull>();
        m_commandsJustReleased[k] = std::make_shared<ControlCommandNull>();
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

        m_commandsPressed[kvp.first] = std::make_shared<ControlCommandNull>();
        m_commandsReleased[kvp.first] = std::make_shared<ControlCommandNull>();
        m_commandsJustPressed[kvp.first] = std::make_shared<ControlCommandNull>();
        m_commandsJustReleased[kvp.first] = std::make_shared<ControlCommandNull>();
    }
}

void KeyboardInput::setCommandPressed(
    std::vector<KeyCode> const& keys, std::shared_ptr<jt::ControlCommandInterface> command)
{
    for (auto const key : keys) {
        m_commandsPressed[key] = command;
    }
}

void KeyboardInput::setCommandReleased(
    std::vector<KeyCode> const& keys, std::shared_ptr<jt::ControlCommandInterface> command)
{
    for (auto const key : keys) {
        m_commandsReleased[key] = command;
    }
}

void KeyboardInput::setCommandJustPressed(
    std::vector<KeyCode> const& keys, std::shared_ptr<jt::ControlCommandInterface> command)
{
    for (auto const key : keys) {
        m_commandsJustPressed[key] = command;
    }
}

void KeyboardInput::setCommandJustReleased(
    std::vector<KeyCode> const& keys, std::shared_ptr<jt::ControlCommandInterface> command)
{
    for (auto const key : keys) {
        m_commandsJustReleased[key] = command;
    }
}

void KeyboardInput::updateCommands(float elapsed)
{
    for (auto const k : jt::getAllKeys()) {
        if (pressed(k)) {
            m_commandsPressed[k]->execute(elapsed);
        }

        if (released(k)) {
            m_commandsReleased[k]->execute(elapsed);
        }

        if (justPressed(k)) {
            m_commandsJustPressed[k]->execute(elapsed);
        }

        if (justReleased(k)) {
            m_commandsJustReleased[k]->execute(elapsed);
        }
    }

    for (auto const k : jt::getAllKeys()) {
        m_commandsPressed[k]->reset();
        m_commandsReleased[k]->reset();
        m_commandsJustPressed[k]->reset();
        m_commandsJustReleased[k]->reset();
    }
}

} // namespace jt
