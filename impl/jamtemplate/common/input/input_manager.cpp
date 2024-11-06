#include "input_manager.hpp"
#include "input/keyboard/keyboard_input_null.hpp"
#include "input/mouse/mouse_input_null.hpp"
#include "performance_measurement.hpp"
#include <input/gamepad/gamepad_input_null.hpp>
#include <tracy/Tracy.hpp>

jt::InputManager::InputManager(std::shared_ptr<jt::MouseInterface> mouse,
    std::shared_ptr<jt::KeyboardInterface> keyboard,
    std::vector<std::shared_ptr<jt::GamepadInterface>> const& gamepads)
    : m_mouse { mouse }
    , m_keyboard { keyboard }
    , m_gamepads { gamepads }
{
    if (m_mouse == nullptr) {
        m_mouse = std::make_shared<jt::MouseInputNull>();
    }
    if (m_keyboard == nullptr) {
        m_keyboard = std::make_shared<jt::KeyboardInputNull>();
    }
}

std::shared_ptr<jt::MouseInterface> jt::InputManager::mouse() { return m_mouse; }

std::shared_ptr<jt::KeyboardInterface> jt::InputManager::keyboard() { return m_keyboard; }

void jt::InputManager::reset()
{
    if (m_mouse) [[likely]] {
        m_mouse->reset();
    }
    if (m_keyboard) [[likely]] {
        m_keyboard->reset();
    }
    for (auto& gp : m_gamepads) {
        gp->reset();
    }
}

void jt::InputManager::update(
    bool /*shouldProcessKeys*/, bool /*shouldProcessMouse*/, MousePosition const& mp, float elapsed)
{
    ZoneScopedN("jt::InputManager::update");
    if (m_mouse) [[likely]] {
        m_mouse->updateMousePosition(mp);
        m_mouse->updateButtons();
    }
    if (m_keyboard) [[likely]] {
        m_keyboard->updateKeys();
        m_keyboard->updateCommands(elapsed);
    }
    for (auto& gp : m_gamepads) {
        gp->update();
    }
}

std::shared_ptr<jt::GamepadInterface> jt::InputManager::gamepad(int gamepad_id)
{
    if (gamepad_id >= 0 && static_cast<std::size_t>(gamepad_id) < m_gamepads.size()) {
        return m_gamepads[gamepad_id];
    }
    return std::make_shared<GamepadInputNull>();
}

size_t jt::InputManager::getNumberOfGamepads() const { return m_gamepads.size(); }
