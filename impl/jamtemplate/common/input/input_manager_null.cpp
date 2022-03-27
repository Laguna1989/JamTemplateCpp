#include "input_manager_null.hpp"

void jt::MouseInputNull::updateMousePosition(jt::MousePosition const& /*mousePosition*/) { }
void jt::MouseInputNull::updateButtons() { }
jt::Vector2f jt::MouseInputNull::getMousePositionWorld() { return jt::Vector2f(); }
jt::Vector2f jt::MouseInputNull::getMousePositionScreen() { return jt::Vector2f(); }
bool jt::MouseInputNull::pressed(jt::MouseButtonCode /*b*/) { return false; }
bool jt::MouseInputNull::released(jt::MouseButtonCode /*b*/) { return false; }
bool jt::MouseInputNull::justPressed(jt::MouseButtonCode /*b*/) { return false; }
bool jt::MouseInputNull::justReleased(jt::MouseButtonCode /*b*/) { return false; }
void jt::MouseInputNull::reset() { }

void jt::KeyboardInputNull::updateKeys() { }
bool jt::KeyboardInputNull::pressed(jt::KeyCode /*k*/) { return false; }
bool jt::KeyboardInputNull::released(jt::KeyCode /*k*/) { return false; }
bool jt::KeyboardInputNull::justPressed(jt::KeyCode /*k*/) { return false; }
bool jt::KeyboardInputNull::justReleased(jt::KeyCode /*k*/) { return false; }
void jt::KeyboardInputNull::reset() { }

std::shared_ptr<jt::MouseInputInterface> jt::InputManagerNull::mouse()
{
    // TODO create class member that is returned
    return std::shared_ptr<MouseInputNull>();
}
std::shared_ptr<jt::KeyboardInputInterface> jt::InputManagerNull::keyboard()
{
    // TODO create class member that is returned
    return std::shared_ptr<KeyboardInputNull>();
}

void jt::InputManagerNull::update(jt::MousePosition const&, float) { }
void jt::InputManagerNull::reset() { }

std::shared_ptr<jt::GamepadInputInterface> jt::InputManagerNull::gamepad(int)
{
    // TODO create class member that is returned
    return std::make_shared<GamepadInputNull>();
}

size_t jt::InputManagerNull::getNumberOfGamepads() const { return 0; }
void jt::GamepadInputNull::update() { }
jt::Vector2f jt::GamepadInputNull::getAxisRaw(jt::GamepadAxisCode) { return Vector2f {}; }
jt::Vector2f jt::GamepadInputNull::getAxis(jt::GamepadAxisCode) { return Vector2f {}; }
void jt::GamepadInputNull::reset() { }

bool jt::GamepadInputNull::pressed(jt::GamepadButtonCode) { return false; }
bool jt::GamepadInputNull::released(jt::GamepadButtonCode) { return false; }
bool jt::GamepadInputNull::justPressed(jt::GamepadButtonCode) { return false; }
bool jt::GamepadInputNull::justReleased(jt::GamepadButtonCode) { return false; }
