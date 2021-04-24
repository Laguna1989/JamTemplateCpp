#ifndef GUARD_JAMTEMPLATE_KEYBOARDINPUT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_KEYBOARDINPUT_HPP_INCLUDEGUARD

#include "InputManagerInterface.hpp"
#include <map>

namespace jt {

class KeyboardInput : public KeyboardInputInterface {
public:
    KeyboardInput();
    virtual void updateKeys() override;

    virtual bool pressed(jt::KeyCode k) override;
    virtual bool released(jt::KeyCode k) override;

    virtual bool justPressed(jt::KeyCode k) override;
    virtual bool justReleased(jt::KeyCode k) override;

    virtual void reset() override;

private:
    std::map<jt::KeyCode, bool> m_pressed;
    std::map<jt::KeyCode, bool> m_released;

    std::map<jt::KeyCode, bool> m_justPressed;
    std::map<jt::KeyCode, bool> m_justReleased;
};

} // namespace jt

#endif
