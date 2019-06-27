#include "InputManager.hpp"

namespace JamTemplate {

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

} // namespace JamTemplate
