#include "input_manager_null.hpp"

namespace jt {
void MouseInputNull::updateMousePosition(MousePosition const& /*mousePosition*/) { }
void MouseInputNull::updateButtons() { }
Vector2 MouseInputNull::getMousePositionWorld() { return jt::Vector2(); }
Vector2 MouseInputNull::getMousePositionScreen() { return jt::Vector2(); }
bool MouseInputNull::pressed(jt::MouseButtonCode /*b*/) { return false; }
bool MouseInputNull::released(jt::MouseButtonCode /*b*/) { return false; }
bool MouseInputNull::justPressed(jt::MouseButtonCode /*b*/) { return false; }
bool MouseInputNull::justReleased(jt::MouseButtonCode /*b*/) { return false; }
void MouseInputNull::reset() { }

void KeyboardInputNull::updateKeys() { }
bool KeyboardInputNull::pressed(jt::KeyCode /*k*/) { return false; }
bool KeyboardInputNull::released(jt::KeyCode /*k*/) { return false; }
bool KeyboardInputNull::justPressed(jt::KeyCode /*k*/) { return false; }
bool KeyboardInputNull::justReleased(jt::KeyCode /*k*/) { return false; }
void KeyboardInputNull::reset() { }

std::shared_ptr<MouseInputInterface> InputManagerNull::mouse()
{
    return std::shared_ptr<MouseInputNull>();
}
std::shared_ptr<KeyboardInputInterface> InputManagerNull::keyboard()
{
    return std::shared_ptr<KeyboardInputNull>();
}

void InputManagerNull::update(MousePosition const&, float) { }
void InputManagerNull::reset() { }

} // namespace jt
