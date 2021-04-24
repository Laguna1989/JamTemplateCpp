#include "MouseInput.hpp"
#include <SFML/Window.hpp>
#include <cstdint>

namespace jt {

namespace {

sf::Mouse::Button toLib(jt::MouseButtonCode key) { return static_cast<sf::Mouse::Button>(key); }

bool libKeyValue(sf::Mouse::Button b) { return sf::Mouse::isButtonPressed(b); }

template <typename CheckFuncArg, typename KeyTypeJT>
void updateValues(std::map<KeyTypeJT, bool>& pressed, std::map<KeyTypeJT, bool>& released,
    std::map<KeyTypeJT, bool>& justPressed, std::map<KeyTypeJT, bool>& justReleased,
    CheckFuncArg check)
{
    for (auto& kvp : pressed) {
        auto const key = kvp.first;
        auto const libkey = toLib(key);
        auto const keyValue = check(libkey);
        if (keyValue) {
            justPressed[key] = (pressed[key] == false);
            justReleased[key] = false;
        } else {
            justReleased[key] = (pressed[key] == true);
            justPressed[key] = false;
        }
        pressed[key] = keyValue;
        released[key] = !keyValue;
    }
}

} // namespace

MouseInput::MouseInput()
{
    auto const allButtons = jt::getAllButtons();
    for (auto const b : allButtons) {
        m_mouseReleased[b] = false;
    }
    reset();
}
void MouseInput::updateMousePosition(MousePosition const& mp)
{
    m_mouseWorldX = mp.window_x;
    m_mouseWorldY = mp.window_y;

    m_mouseScreenX = mp.screen_x;
    m_mouseScreenY = mp.screen_y;
}
void MouseInput::updateButtons()
{
    updateValues(m_mousePressed, m_mouseReleased, m_mouseJustPressed, m_mouseJustReleased,
        [](auto b) { return sf::Mouse::isButtonPressed(b); });
}

jt::Vector2 MouseInput::getMousePositionWorld()
{
    return jt::Vector2 { m_mouseWorldX, m_mouseWorldY };
}
jt::Vector2 MouseInput::getMousePositionScreen()
{
    return jt::Vector2 { m_mouseScreenX, m_mouseScreenY };
}

bool MouseInput::pressed(jt::MouseButtonCode b) { return m_mousePressed[b]; }
bool MouseInput::released(jt::MouseButtonCode b) { return m_mouseReleased[b]; }
bool MouseInput::justPressed(jt::MouseButtonCode b) { return m_mouseJustPressed[b]; }
bool MouseInput::justReleased(jt::MouseButtonCode b) { return m_mouseJustReleased[b]; }

void MouseInput::reset()
{
    for (auto& kvp : m_mouseReleased) {
        m_mousePressed[kvp.first] = false;
        m_mouseReleased[kvp.first] = false;
        m_mouseJustPressed[kvp.first] = false;
        m_mouseJustReleased[kvp.first] = false;
    }
    m_mouseScreenX = 0.0f;
    m_mouseScreenY = 0.0f;
    m_mouseWorldX = 0.0f;
    m_mouseWorldY = 0.0f;
}

} // namespace jt
