#include "InputManager.hpp"
namespace jt {

namespace InputHelper {

std::vector<jt::MouseButtonCode> getAllMouseButtons()
{
    auto const maxValue = static_cast<uint32_t>(jt::MouseButtonCode::ButtonCount);
    std::vector<jt::MouseButtonCode> values(maxValue, jt::MouseButtonCode::MBLeft);
    for (uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<jt::MouseButtonCode>(i);
    }
    return values;
}
} // namespace InputHelper

std::map<jt::KeyCode, bool> InputManager::m_pressed;
std::map<jt::KeyCode, bool> InputManager::m_released;

std::map<jt::KeyCode, bool> InputManager::m_justPressed;
std::map<jt::KeyCode, bool> InputManager::m_justReleased;

std::map<jt::MouseButtonCode, bool> InputManager::m_mousePressed;
std::map<jt::MouseButtonCode, bool> InputManager::m_mouseJustPressed;
std::map<jt::MouseButtonCode, bool> InputManager::m_mouseReleased;
std::map<jt::MouseButtonCode, bool> InputManager::m_mouseJustReleased;

float InputManager::m_mouseX;
float InputManager::m_mouseY;

float InputManager::m_mouseScreenX;
float InputManager::m_mouseScreenY;

float InputManager::m_age;

void InputManager::update(float mx, float my, float mxs, float mys, float elapsed)
{
    setup();

    float const old_time = m_age;
    m_age += elapsed;
    if (old_time <= 0.1f) {
        return;
    }

    m_mouseX = mx;
    m_mouseY = my;

    m_mouseScreenX = mxs;
    m_mouseScreenY = mys;

    for (auto& kvp : m_pressed) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(kvp.first))) {
            if (m_pressed[kvp.first] == false)
                m_justPressed[kvp.first] = true;
            else
                m_justPressed[kvp.first] = false;
        } else {
            if (m_pressed[kvp.first] == true)
                m_justReleased[kvp.first] = true;
            else
                m_justReleased[kvp.first] = false;
        }
        m_pressed[kvp.first]
            = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(kvp.first));
        m_released[kvp.first]
            = !sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(kvp.first));
    }

    // std::cout << m_pressed[jt::KeyCode::I] << " " << m_released[jt::KeyCode::I] <<" "
    // << m_justPressed[jt::KeyCode::I]<< "\n";

    for (auto& kvp : m_mousePressed) {
        if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(kvp.first))) {
            if (m_mousePressed[kvp.first] == false)
                m_mouseJustPressed[kvp.first] = true;
            else
                m_mouseJustPressed[kvp.first] = false;

        } else {
            if (m_mousePressed[kvp.first] == true)
                m_mouseJustReleased[kvp.first] = true;
            else
                m_mouseJustReleased[kvp.first] = false;
        }
        m_mousePressed[kvp.first]
            = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(kvp.first));
        m_mouseReleased[kvp.first]
            = !sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(kvp.first));
    }
    // std::cout << "a " << m_lmb_pressed << " " << m_lmb_released << " " << m_lmb_justPressed << "
    // " << m_lmb_justReleased << std::endl;
}

jt::vector2 InputManager::getMousePositionWorld() { return jt::vector2 { m_mouseX, m_mouseY }; }

jt::vector2 InputManager::getMousePositionScreen()
{
    return jt::vector2 { m_mouseScreenX, m_mouseScreenY };
}

bool InputManager::pressed(jt::KeyCode k) { return m_pressed[k]; }
bool InputManager::pressed(jt::MouseButtonCode b) { return m_mousePressed[b]; }

bool InputManager::released(jt::KeyCode k) { return m_released[k]; }
bool InputManager::released(jt::MouseButtonCode b) { return m_mouseReleased[b]; }

bool InputManager::justPressed(jt::KeyCode k) { return m_justPressed[k]; }
bool InputManager::justPressed(jt::MouseButtonCode b) { return m_mouseJustPressed[b]; }

bool InputManager::justReleased(jt::KeyCode k) { return m_justReleased[k]; }

bool InputManager::justReleased(jt::MouseButtonCode b) { return m_mouseJustReleased[b]; }

void InputManager::reset()
{
    m_age = 0.0f;
    for (auto& kvp : m_released) {
        m_pressed[kvp.first] = false;
        m_released[kvp.first] = false;
        m_justPressed[kvp.first] = false;
        m_justReleased[kvp.first] = false;
    }
    for (auto& kvp : m_mouseReleased) {
        m_mousePressed[kvp.first] = false;
        m_mouseReleased[kvp.first] = false;
        m_mouseJustPressed[kvp.first] = false;
        m_mouseJustReleased[kvp.first] = false;
    }
    m_mouseScreenX = 0.0f;
    m_mouseScreenY = 0.0f;
    m_mouseX = 0.0f;
    m_mouseY = 0.0f;
}

void InputManager::setup()
{
    if (m_released.empty()) {
        // std::cout << "inputmanager setup\n";
        auto const allKeys = jt::getAllKeys();
        for (auto const k : allKeys) {
            m_released[k] = false;
        }

        auto const allButtons = InputHelper::getAllMouseButtons();
        for (auto const b : allButtons) {
            m_mouseReleased[b] = false;
        }
        reset();
    }
}

} // namespace jt
