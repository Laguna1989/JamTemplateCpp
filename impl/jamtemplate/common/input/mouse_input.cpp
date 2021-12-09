#include "mouse_input.hpp"
#include "input_helper.hpp"

namespace jt {

MouseInput::MouseInput(MouseButtonCheckFunction checkFunction)
    : m_checkFunction { std::move(checkFunction) }
{
    auto const allButtons = jt::getAllButtons();
    // note: do not call the virtual reset() function here, as this is the constructor
    for (auto const b : allButtons) {
        m_mousePressed[b] = false;
        m_mouseReleased[b] = false;
        m_mouseJustPressed[b] = false;
        m_mouseJustReleased[b] = false;
    }
    m_mouseScreenX = 0.0f;
    m_mouseScreenY = 0.0f;
    m_mouseWorldX = 0.0f;
    m_mouseWorldY = 0.0f;
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
    jt::inputhelper::updateValues(m_mousePressed, m_mouseReleased, m_mouseJustPressed,
        m_mouseJustReleased, [this](auto b) { return m_checkFunction(b); });
}

jt::Vector2f MouseInput::getMousePositionWorld()
{
    return jt::Vector2f { m_mouseWorldX, m_mouseWorldY };
}

jt::Vector2f MouseInput::getMousePositionScreen()
{
    return jt::Vector2f { m_mouseScreenX, m_mouseScreenY };
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
