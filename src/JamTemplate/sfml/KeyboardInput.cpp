
#include "KeyboardInput.hpp"
#include <SFML/Window.hpp>
#include <cstdint>

namespace jt {

namespace {
sf::Keyboard::Key toLib(jt::KeyCode key) { return static_cast<sf::Keyboard::Key>(key); }

bool libKeyValue(sf::Keyboard::Key k) { return sf::Keyboard::isKeyPressed(k); }

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

KeyboardInput::KeyboardInput()
{
    auto const allKeys = jt::getAllKeys();
    for (auto const k : allKeys) {
        m_released[k] = false;
    }

    reset();
}

void KeyboardInput::updateKeys()
{
    updateValues(m_pressed, m_released, m_justPressed, m_justReleased,
        [](auto k) { return sf::Keyboard::isKeyPressed(k); });
}
bool KeyboardInput::pressed(jt::KeyCode k) { return m_pressed[k]; }
bool KeyboardInput::released(jt::KeyCode k) { return m_released[k]; }
bool KeyboardInput::justPressed(jt::KeyCode k) { return m_justPressed[k]; }
bool KeyboardInput::justReleased(jt::KeyCode k) { return m_justReleased[k]; }
void KeyboardInput::reset()
{
    for (auto& kvp : m_released) {
        m_pressed[kvp.first] = false;
        m_released[kvp.first] = false;
        m_justPressed[kvp.first] = false;
        m_justReleased[kvp.first] = false;
    }
}
} // namespace jt
