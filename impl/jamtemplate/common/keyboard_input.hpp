#ifndef GUARD_JAMTEMPLATE_KEYBOARDINPUT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_KEYBOARDINPUT_HPP_INCLUDEGUARD

#include "input_manager_interface.hpp"
#include "keyboard_input_lib.hpp"
#include <functional>
#include <map>

namespace jt {

class KeyboardInput : public KeyboardInputInterface {
public:
    using KeyboardKeyCheckFunction = std::function<bool(jt::KeyCode)>;
    KeyboardInput(KeyboardKeyCheckFunction checkFunc = [](auto k) { return libKeyValue(k); });

    virtual void updateKeys() override;

    virtual bool pressed(jt::KeyCode k) override;
    virtual bool released(jt::KeyCode k) override;

    virtual bool justPressed(jt::KeyCode k) override;
    virtual bool justReleased(jt::KeyCode k) override;

    virtual void reset() override;

private:
    KeyboardKeyCheckFunction m_checkFunc;
    std::map<jt::KeyCode, bool> m_pressed {};
    std::map<jt::KeyCode, bool> m_released {};

    std::map<jt::KeyCode, bool> m_justPressed {};
    std::map<jt::KeyCode, bool> m_justReleased {};
};

} // namespace jt

#endif
