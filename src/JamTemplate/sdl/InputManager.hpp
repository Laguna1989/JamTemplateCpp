#ifndef GUARD_JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD

#include "KeyCodes.hpp"
#include "Vector.hpp"
#include <SDL.h>
#include <iostream>
#include <map>
#include <vector>

namespace jt {

class InputManager {
public:
    InputManager() = delete;

    static void update(float mx, float my, float mxs, float mys, float elapsed);

    static jt::Vector2 getMousePositionWorld();
    static jt::Vector2 getMousePositionScreen();

    static bool pressed(jt::KeyCode k);
    static bool pressed(jt::MouseButtonCode b);

    static bool released(jt::KeyCode k);
    static bool released(jt::MouseButtonCode b);

    static bool justPressed(jt::KeyCode k);
    static bool justPressed(jt::MouseButtonCode b);

    static bool justReleased(jt::KeyCode k);
    static bool justReleased(jt::MouseButtonCode b);

    static void reset();

private:
    static std::map<jt::KeyCode, bool> m_pressed;
    static std::map<jt::KeyCode, bool> m_released;

    static std::map<jt::KeyCode, bool> m_justPressed;
    static std::map<jt::KeyCode, bool> m_justReleased;

    static std::map<jt::MouseButtonCode, bool> m_mousePressed;
    static std::map<jt::MouseButtonCode, bool> m_mouseJustPressed;

    static std::map<jt::MouseButtonCode, bool> m_mouseReleased;
    static std::map<jt::MouseButtonCode, bool> m_mouseJustReleased;

    static float m_mouseX;
    static float m_mouseY;

    static float m_mouseScreenX;
    static float m_mouseScreenY;

    static float m_age;

    static void setup();
};

} // namespace jt

#endif
