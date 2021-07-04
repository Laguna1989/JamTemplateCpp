#ifndef GUARD_JAMTEMPLATE_INPUTMANAGERINTERFACE_HPP
#define GUARD_JAMTEMPLATE_INPUTMANAGERINTERFACE_HPP

#include "key_codes.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {

struct MousePosition {
    float window_x;
    float window_y;

    float screen_x;
    float screen_y;
};

class MouseInputInterface {
public:
    virtual ~MouseInputInterface() = default;
    virtual void updateMousePosition(MousePosition const& mp) = 0;
    virtual void updateButtons() = 0;

    virtual jt::Vector2 getMousePositionWorld() = 0;
    virtual jt::Vector2 getMousePositionScreen() = 0;

    virtual bool pressed(jt::MouseButtonCode b) = 0;
    virtual bool justReleased(jt::MouseButtonCode b) = 0;
    virtual bool justPressed(jt::MouseButtonCode b) = 0;
    virtual bool released(jt::MouseButtonCode b) = 0;

    virtual void reset() = 0;
};

class KeyboardInputInterface {
public:
    virtual ~KeyboardInputInterface() = default;
    virtual void updateKeys() = 0;

    virtual bool pressed(jt::KeyCode k) = 0;
    virtual bool released(jt::KeyCode k) = 0;
    virtual bool justPressed(jt::KeyCode k) = 0;
    virtual bool justReleased(jt::KeyCode k) = 0;

    virtual void reset() = 0;
};

class InputManagerInterface {
public:
    virtual ~InputManagerInterface() = default;
    virtual std::shared_ptr<MouseInputInterface> mouse() = 0;
    virtual std::shared_ptr<KeyboardInputInterface> keyboard() = 0;
    virtual void reset() = 0;
};

} // namespace jt
#endif
