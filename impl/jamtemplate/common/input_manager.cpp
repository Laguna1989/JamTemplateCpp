#include "input_manager.hpp"

namespace jt {

InputManager::InputManager(
    std::shared_ptr<MouseInputInterface> mouse, std::shared_ptr<KeyboardInputInterface> keyboard)
    : m_mouse { mouse }
    , m_keyboard { keyboard }
{
}

std::shared_ptr<MouseInputInterface> InputManager::mouse() { return m_mouse; }
std::shared_ptr<KeyboardInputInterface> InputManager::keyboard() { return m_keyboard; }

void InputManager::reset()
{
    if (m_mouse) {
        m_mouse->reset();
    }
    if (m_keyboard) {
        m_keyboard->reset();
    }
}
void InputManager::update(MousePosition const& mp, float elapsed)
{
    if (m_mouse) {
        m_mouse->updateMousePosition(mp);
        m_mouse->updateButtons();
    }
    if (m_keyboard) {
        m_keyboard->updateKeys();
        m_keyboard->updateCommands(elapsed);
    }
}

} // namespace jt
