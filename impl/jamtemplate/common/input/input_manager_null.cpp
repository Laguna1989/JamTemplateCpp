#include "input_manager_null.hpp"
#include <input/gamepad/gamepad_input_null.hpp>
#include <input/keyboard/keyboard_input_null.hpp>
#include <input/mouse/mouse_input_null.hpp>

jt::InputManagerNull::InputManagerNull()
    : m_mouse { std::make_shared<MouseInputNull>() }
    , m_keyboard { std::make_shared<KeyboardInputNull>() }
    , m_gamepad { std::make_shared<GamepadInputNull>() }
{
}

std::shared_ptr<jt::MouseInterface> jt::InputManagerNull::mouse() { return m_mouse; }

std::shared_ptr<jt::KeyboardInterface> jt::InputManagerNull::keyboard() { return m_keyboard; }

std::shared_ptr<jt::GamepadInterface> jt::InputManagerNull::gamepad(int) { return m_gamepad; }

void jt::InputManagerNull::update(bool /*shouldProcessKeys*/, bool /*shouldProcessMouse*/,
    MousePosition const& /*mp*/, float /*elapsed*/)
{
}
void jt::InputManagerNull::reset() { }

size_t jt::InputManagerNull::getNumberOfGamepads() const { return 0; }
