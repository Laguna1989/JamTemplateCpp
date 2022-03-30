#include "mouse_input_null.hpp"

void jt::MouseInputNull::updateMousePosition(jt::MousePosition const& /*mousePosition*/) { }
void jt::MouseInputNull::updateButtons() { }
jt::Vector2f jt::MouseInputNull::getMousePositionWorld() { return jt::Vector2f(); }
jt::Vector2f jt::MouseInputNull::getMousePositionScreen() { return jt::Vector2f(); }
bool jt::MouseInputNull::pressed(jt::MouseButtonCode /*b*/) { return false; }
bool jt::MouseInputNull::released(jt::MouseButtonCode /*b*/) { return false; }
bool jt::MouseInputNull::justPressed(jt::MouseButtonCode /*b*/) { return false; }
bool jt::MouseInputNull::justReleased(jt::MouseButtonCode /*b*/) { return false; }
void jt::MouseInputNull::reset() { }
