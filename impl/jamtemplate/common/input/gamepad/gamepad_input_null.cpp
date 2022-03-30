#include "gamepad_input_null.hpp"

void jt::GamepadInputNull::update() { }
jt::Vector2f jt::GamepadInputNull::getAxisRaw(jt::GamepadAxisCode) { return Vector2f {}; }
jt::Vector2f jt::GamepadInputNull::getAxis(jt::GamepadAxisCode) { return Vector2f {}; }
void jt::GamepadInputNull::reset() { }

bool jt::GamepadInputNull::pressed(jt::GamepadButtonCode) { return false; }
bool jt::GamepadInputNull::released(jt::GamepadButtonCode) { return false; }
bool jt::GamepadInputNull::justPressed(jt::GamepadButtonCode) { return false; }
bool jt::GamepadInputNull::justReleased(jt::GamepadButtonCode) { return false; }
