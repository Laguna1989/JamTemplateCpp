#include "InputManager.hpp"

namespace JamTemplate {

namespace InputHelper {

std::vector<sf::Keyboard::Key> getAllKeys()
{
    auto const maxValue = static_cast<uint32_t>(sf::Keyboard::Key::KeyCount);
    std::vector<sf::Keyboard::Key> values(maxValue, sf::Keyboard::A);
    for (uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<sf::Keyboard::Key>(i);
    }
    return values;
}

std::vector<sf::Mouse::Button> getAllMouseButtons()
{
    auto const maxValue = static_cast<uint32_t>(sf::Mouse::Button::ButtonCount);
    std::vector<sf::Mouse::Button> values(maxValue, sf::Mouse::Button::Left);
    for (uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<sf::Mouse::Button>(i);
    }
    return values;
}
} // namespace InputHelper

std::map<sf::Keyboard::Key, bool> InputManager::m_pressed;
std::map<sf::Keyboard::Key, bool> InputManager::m_released;

std::map<sf::Keyboard::Key, bool> InputManager::m_justPressed;
std::map<sf::Keyboard::Key, bool> InputManager::m_justReleased;

std::map<sf::Mouse::Button, bool> InputManager::m_mousePressed;
std::map<sf::Mouse::Button, bool> InputManager::m_mouseJustPressed;
std::map<sf::Mouse::Button, bool> InputManager::m_mouseReleased;
std::map<sf::Mouse::Button, bool> InputManager::m_mouseJustReleased;

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
        if (sf::Keyboard::isKeyPressed(kvp.first)) {
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
        m_pressed[kvp.first] = sf::Keyboard::isKeyPressed(kvp.first);
        m_released[kvp.first] = !sf::Keyboard::isKeyPressed(kvp.first);
    }

    // std::cout << m_pressed[sf::Keyboard::Key::I] << " " << m_released[sf::Keyboard::Key::I] <<" "
    // << m_justPressed[sf::Keyboard::Key::I]<< "\n";

    for (auto& kvp : m_mousePressed) {
        if (sf::Mouse::isButtonPressed(kvp.first)) {
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
        m_mousePressed[kvp.first] = sf::Mouse::isButtonPressed(kvp.first);
        m_mouseReleased[kvp.first] = !sf::Mouse::isButtonPressed(kvp.first);
    }
    // std::cout << "a " << m_lmb_pressed << " " << m_lmb_released << " " << m_lmb_justPressed << "
    // " << m_lmb_justReleased << std::endl;
}

sf::Vector2f InputManager::getMousePositionWorld() { return sf::Vector2f(m_mouseX, m_mouseY); }

sf::Vector2f InputManager::getMousePositionScreen()
{
    return sf::Vector2f(m_mouseScreenX, m_mouseScreenY);
}

bool InputManager::pressed(sf::Keyboard::Key k) { return m_pressed[k]; }
bool InputManager::pressed(sf::Mouse::Button b) { return m_mousePressed[b]; }

bool InputManager::released(sf::Keyboard::Key k) { return m_released[k]; }
bool InputManager::released(sf::Mouse::Button b) { return m_mouseReleased[b]; }

bool InputManager::justPressed(sf::Keyboard::Key k) { return m_justPressed[k]; }
bool InputManager::justPressed(sf::Mouse::Button b) { return m_mouseJustPressed[b]; }

bool InputManager::justReleased(sf::Keyboard::Key k) { return m_justReleased[k]; }

bool InputManager::justReleased(sf::Mouse::Button b) { return m_mouseJustReleased[b]; }

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
}

void InputManager::setup()
{
    if (m_released.empty()) {
        std::cout << "inputmanager setup\n";
        auto const allKeys = InputHelper::getAllKeys();
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

} // namespace JamTemplate
