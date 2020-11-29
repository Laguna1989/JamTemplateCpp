#ifndef JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD

#include "KeyCodes.hpp"
#include "vector.hpp"
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <vector>

namespace jt {
namespace InputHelper {

std::vector<sf::Mouse::Button> getAllMouseButtons();

} // namespace InputHelper

class InputManager {
public:
    InputManager() = delete;

    static void update(float mx, float my, float mxs, float mys, float elapsed);

    static jt::vector2 getMousePositionWorld();
    static jt::vector2 getMousePositionScreen();

    static bool pressed(jt::KeyCode k);
    static bool pressed(sf::Mouse::Button b);

    static bool released(jt::KeyCode k);
    static bool released(sf::Mouse::Button b);

    static bool justPressed(jt::KeyCode k);
    static bool justPressed(sf::Mouse::Button b);

    static bool justReleased(jt::KeyCode k);
    static bool justReleased(sf::Mouse::Button b);

    static void reset();

private:
    static std::map<jt::KeyCode, bool> m_pressed;
    static std::map<jt::KeyCode, bool> m_released;

    static std::map<jt::KeyCode, bool> m_justPressed;
    static std::map<jt::KeyCode, bool> m_justReleased;

    static std::map<sf::Mouse::Button, bool> m_mousePressed;
    static std::map<sf::Mouse::Button, bool> m_mouseJustPressed;

    static std::map<sf::Mouse::Button, bool> m_mouseReleased;
    static std::map<sf::Mouse::Button, bool> m_mouseJustReleased;

    static float m_mouseX;
    static float m_mouseY;

    static float m_mouseScreenX;
    static float m_mouseScreenY;

    static float m_age;

    static void setup();
};

} // namespace jt

#endif
