#include "input_manager_null.hpp"
#include "input/gamepad/gamepad_input_null.hpp"
#include "input/keyboard/keyboard_input_null.hpp"
#include "input/mouse/mouse_input_null.hpp"

std::shared_ptr<jt::MouseInterface> jt::InputManagerNull::mouse()
{
    // TODO create class member that is returned
    return std::make_shared<MouseInputNull>();
}

std::shared_ptr<jt::KeyboardInterface> jt::InputManagerNull::keyboard()
{
    // TODO create class member that is returned
    return std::make_shared<KeyboardInputNull>();
}

std::shared_ptr<jt::GamepadInterface> jt::InputManagerNull::gamepad(int)
{
    // TODO create class member that is returned
    return std::make_shared<GamepadInputNull>();
}

void jt::InputManagerNull::update(jt::MousePosition const&, float) { }
void jt::InputManagerNull::reset() { }

size_t jt::InputManagerNull::getNumberOfGamepads() const { return 0; }
