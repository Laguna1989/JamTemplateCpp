#include "keyboard_input_selected_keys.hpp"
#include "performance_measurement.hpp"
#include <input/control_commands/control_command_null.hpp>
#include <input/input_helper.hpp>
#include <tracy/Tracy.hpp>

jt::KeyboardInputSelectedKeys::KeyboardInputSelectedKeys(
    KeyboardInputSelectedKeys::KeyboardKeyCheckFunction checkFunc)
    : m_checkFunc { std::move(checkFunc) }
{
}

void jt::KeyboardInputSelectedKeys::listenForKey(jt::KeyCode k)
{
    m_pressed[k] = false;
    m_released[k] = false;
    m_justPressed[k] = false;
    m_justReleased[k] = false;

    m_commandsPressed[k] = std::make_shared<ControlCommandNull>();
    m_commandsReleased[k] = std::make_shared<ControlCommandNull>();
    m_commandsJustPressed[k] = std::make_shared<ControlCommandNull>();
    m_commandsJustReleased[k] = std::make_shared<ControlCommandNull>();
}

void jt::KeyboardInputSelectedKeys::updateKeys()
{
    ZoneScopedN("jt::KeyboardInputSelectedKeys::updateKeys");
    jt::inputhelper::updateValues(m_pressed, m_released, m_justPressed, m_justReleased,
        [this](auto k) { return m_checkFunc(k); });
}

bool jt::KeyboardInputSelectedKeys::pressed(jt::KeyCode k)
{
    return m_pressed.contains(k) && m_pressed[k];
}

bool jt::KeyboardInputSelectedKeys::released(jt::KeyCode k)
{
    return m_pressed.contains(k) && m_released[k];
}

bool jt::KeyboardInputSelectedKeys::justPressed(jt::KeyCode k)
{
    return m_pressed.contains(k) && m_justPressed[k];
}

bool jt::KeyboardInputSelectedKeys::justReleased(jt::KeyCode k)
{
    return m_pressed.contains(k) && m_justReleased[k];
}

void jt::KeyboardInputSelectedKeys::reset()
{
    for (auto const& kvp : m_released) {
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

void jt::KeyboardInputSelectedKeys::setCommandJustPressed(
    std::vector<KeyCode> const& keys, std::shared_ptr<jt::ControlCommandInterface> command)
{
    for (auto const key : keys) {
        m_commandsJustPressed[key] = command;
    }
}

void jt::KeyboardInputSelectedKeys::setCommandPressed(
    std::vector<KeyCode> const& keys, std::shared_ptr<jt::ControlCommandInterface> command)
{
    for (auto const key : keys) {
        m_commandsPressed[key] = command;
    }
}

void jt::KeyboardInputSelectedKeys::setCommandReleased(
    std::vector<KeyCode> const& keys, std::shared_ptr<jt::ControlCommandInterface> command)
{
    for (auto const key : keys) {
        m_commandsReleased[key] = command;
    }
}

void jt::KeyboardInputSelectedKeys::setCommandJustReleased(
    std::vector<KeyCode> const& keys, std::shared_ptr<jt::ControlCommandInterface> command)
{
    for (auto const key : keys) {
        m_commandsJustReleased[key] = command;
    }
}

void jt::KeyboardInputSelectedKeys::updateCommands(float elapsed)
{
    for (auto const kvp : m_pressed) {
        auto const k = kvp.first;
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

    for (auto const kvp : m_pressed) {
        auto const k = kvp.first;
        m_commandsPressed[k]->reset();
        m_commandsReleased[k]->reset();
        m_commandsJustPressed[k]->reset();
        m_commandsJustReleased[k]->reset();
    }
}
