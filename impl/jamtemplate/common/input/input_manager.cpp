#include "input_manager.hpp"
#include "input_manager_null.hpp"

jt::InputManager::InputManager(std::shared_ptr<jt::MouseInputInterface> mouse,
    std::shared_ptr<jt::KeyboardInputInterface> keyboard,
    std::vector<std::shared_ptr<jt::GamepadInputInterface>> gamepads)
    : m_mouse { mouse }
    , m_keyboard { keyboard }
    , m_gamepads { gamepads }
{
}

std::shared_ptr<jt::MouseInputInterface> jt::InputManager::mouse() { return m_mouse; }
std::shared_ptr<jt::KeyboardInputInterface> jt::InputManager::keyboard() { return m_keyboard; }

void jt::InputManager::reset()
{
    if (m_mouse) {
        m_mouse->reset();
    }
    if (m_keyboard) {
        m_keyboard->reset();
    }
    for (auto& gp : m_gamepads) {
        gp->reset();
    }
}

void jt::InputManager::update(jt::MousePosition const& mp, float elapsed)
{
    if (m_mouse) {
        m_mouse->updateMousePosition(mp);
        m_mouse->updateButtons();
    }
    if (m_keyboard) {
        m_keyboard->updateKeys();
        m_keyboard->updateCommands(elapsed);
    }
    for (auto& gp : m_gamepads) {
        gp->update();
    }
}

std::shared_ptr<jt::GamepadInputInterface> jt::InputManager::gamepad(int gamepad_id)
{
    if (gamepad_id >= 0 && static_cast<std::size_t>(gamepad_id) < m_gamepads.size()) {
        return m_gamepads[gamepad_id];
    }
    return std::make_shared<GamepadInputNull>();
}

size_t jt::InputManager::getNumberOfGamepads() const { return m_gamepads.size(); }
