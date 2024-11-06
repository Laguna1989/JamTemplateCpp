#include "mouse_input.hpp"
#include "performance_measurement.hpp"
#include <input/input_helper.hpp>
#include <tracy/Tracy.hpp>

jt::MouseInput::MouseInput(MouseButtonCheckFunction checkFunction)
    : m_checkFunction { std::move(checkFunction) }
{
    // note: do not call the virtual reset() function here, as this is the constructor
    for (auto const b : jt::getAllMouseButtons()) {
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

void jt::MouseInput::updateMousePosition(jt::MousePosition const& mp)
{
    ZoneScopedN("jt::MouseInput::updateMousePosition");
    m_mouseWorldX = mp.window_x;
    m_mouseWorldY = mp.window_y;

    m_mouseScreenX = mp.screen_x;
    m_mouseScreenY = mp.screen_y;
}

void jt::MouseInput::updateButtons()
{
    ZoneScopedN("jt::MouseInput::updateButtons");
    jt::inputhelper::updateValues(m_mousePressed, m_mouseReleased, m_mouseJustPressed,
        m_mouseJustReleased, [this](auto b) { return m_checkFunction(b); });
}

jt::Vector2f jt::MouseInput::getMousePositionWorld()
{
    return jt::Vector2f { m_mouseWorldX, m_mouseWorldY };
}

jt::Vector2f jt::MouseInput::getMousePositionScreen()
{
    return jt::Vector2f { m_mouseScreenX, m_mouseScreenY };
}

bool jt::MouseInput::pressed(jt::MouseButtonCode b) { return m_mousePressed[b]; }

bool jt::MouseInput::released(jt::MouseButtonCode b) { return m_mouseReleased[b]; }

bool jt::MouseInput::justPressed(jt::MouseButtonCode b) { return m_mouseJustPressed[b]; }

bool jt::MouseInput::justReleased(jt::MouseButtonCode b) { return m_mouseJustReleased[b]; }

void jt::MouseInput::reset()
{
    for (auto const& kvp : m_mouseReleased) {
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
