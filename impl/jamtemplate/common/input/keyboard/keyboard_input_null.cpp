#include "keyboard_input_null.hpp"

void jt::KeyboardInputNull::updateKeys() { }
bool jt::KeyboardInputNull::pressed(jt::KeyCode /*k*/) { return false; }
bool jt::KeyboardInputNull::released(jt::KeyCode /*k*/) { return false; }
bool jt::KeyboardInputNull::justPressed(jt::KeyCode /*k*/) { return false; }
bool jt::KeyboardInputNull::justReleased(jt::KeyCode /*k*/) { return false; }
void jt::KeyboardInputNull::reset() { }

void jt::KeyboardInputNull::setCommandJustPressed(
    std::vector<KeyCode> const& /*key*/, std::shared_ptr<jt::ControlCommandInterface> /*command*/)
{
}
void jt::KeyboardInputNull::setCommandPressed(
    std::vector<KeyCode> const& /*key*/, std::shared_ptr<jt::ControlCommandInterface> /*command*/)
{
}
void jt::KeyboardInputNull::setCommandReleased(
    std::vector<KeyCode> const& /*key*/, std::shared_ptr<jt::ControlCommandInterface> /*command*/)
{
}
void jt::KeyboardInputNull::setCommandJustReleased(
    std::vector<KeyCode> const& /*key*/, std::shared_ptr<jt::ControlCommandInterface> /*command*/)
{
}
void jt::KeyboardInputNull::updateCommands(float /*elapsed*/) { }
