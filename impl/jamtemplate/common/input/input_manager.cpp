#include "input_manager.hpp"

jt::InputManager::InputManager(std::shared_ptr<jt::MouseInputInterface> mouse,
    std::shared_ptr<jt::KeyboardInputInterface> keyboard)
    : m_mouse { mouse }
    , m_keyboard { keyboard }
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
}
