#include "InputManager.hpp"

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

} // namespace jt
