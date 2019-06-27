#ifndef JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD

#include <SFML/Window.hpp>
#include <iostream>
#include <map>

namespace JamTemplate {

class InputManager {
public:
    InputManager() = delete;

    static void update(float mx, float my, float mxs, float mys)
    {
        setup();

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

        //std::cout << m_pressed[sf::Keyboard::Key::I] << " " << m_released[sf::Keyboard::Key::I] <<" " << m_justPressed[sf::Keyboard::Key::I]<< "\n";

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
        //std::cout << "a " << m_lmb_pressed << " " << m_lmb_released << " " << m_lmb_justPressed << " " << m_lmb_justReleased << std::endl;
    }

    static sf::Vector2f getMousePositionWorld()
    {
        return sf::Vector2f(m_mouseX, m_mouseY);
    }

    static sf::Vector2f getMousePositionScreen()
    {
        return sf::Vector2f(m_mouseScreenX, m_mouseScreenY);
    }

    static bool pressed(sf::Keyboard::Key k)
    {
        return m_pressed[k];
    }
    static bool pressed(sf::Mouse::Button b)
    {
        return m_mousePressed[b];
    }

    static bool released(sf::Keyboard::Key k)
    {
        return m_released[k];
    }
    static bool released(sf::Mouse::Button b)
    {
        return m_mouseReleased[b];
    }

    static bool justPressed(sf::Keyboard::Key k)
    {
        return m_justPressed[k];
    }
    static bool justPressed(sf::Mouse::Button b)
    {
        return m_mouseJustPressed[b];
    }

    static bool justReleased(sf::Keyboard::Key k)
    {
        return m_justReleased[k];
    }
    static bool justReleased(sf::Mouse::Button b)
    {
        return m_mouseJustReleased[b];
    }

    static void reset()
    {
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

private:
    static std::map<sf::Keyboard::Key, bool> m_pressed;
    static std::map<sf::Keyboard::Key, bool> m_released;

    static std::map<sf::Keyboard::Key, bool> m_justPressed;
    static std::map<sf::Keyboard::Key, bool> m_justReleased;

    static std::map<sf::Mouse::Button, bool> m_mousePressed;
    static std::map<sf::Mouse::Button, bool> m_mouseJustPressed;

    static std::map<sf::Mouse::Button, bool> m_mouseReleased;
    static std::map<sf::Mouse::Button, bool> m_mouseJustReleased;

    static float m_mouseX;
    static float m_mouseY;

    static float m_mouseScreenX;
    static float m_mouseScreenY;

    static void setup()
    {
        if (m_released.empty()) {
            std::cout << "inputmanager setup\n";
            m_released[sf::Keyboard::Key::Q] = false;
            m_released[sf::Keyboard::Key::W] = false;
            m_released[sf::Keyboard::Key::E] = false;
            m_released[sf::Keyboard::Key::R] = false;
            m_released[sf::Keyboard::Key::T] = false;
            m_released[sf::Keyboard::Key::Z] = false;
            m_released[sf::Keyboard::Key::U] = false;
            m_released[sf::Keyboard::Key::I] = false;
            m_released[sf::Keyboard::Key::O] = false;
            m_released[sf::Keyboard::Key::P] = false;
            m_released[sf::Keyboard::Key::A] = false;
            m_released[sf::Keyboard::Key::S] = false;
            m_released[sf::Keyboard::Key::D] = false;
            m_released[sf::Keyboard::Key::F] = false;
            m_released[sf::Keyboard::Key::G] = false;
            m_released[sf::Keyboard::Key::H] = false;
            m_released[sf::Keyboard::Key::J] = false;
            m_released[sf::Keyboard::Key::K] = false;
            m_released[sf::Keyboard::Key::L] = false;
            m_released[sf::Keyboard::Key::Y] = false;
            m_released[sf::Keyboard::Key::X] = false;
            m_released[sf::Keyboard::Key::C] = false;
            m_released[sf::Keyboard::Key::V] = false;
            m_released[sf::Keyboard::Key::B] = false;
            m_released[sf::Keyboard::Key::N] = false;
            m_released[sf::Keyboard::Key::M] = false;

            m_released[sf::Keyboard::Key::Down] = false;
            m_released[sf::Keyboard::Key::Up] = false;
            m_released[sf::Keyboard::Key::Left] = false;
            m_released[sf::Keyboard::Key::Right] = false;

            m_released[sf::Keyboard::Key::Space] = false;
            m_released[sf::Keyboard::Key::Return] = false;
            m_released[sf::Keyboard::Key::LShift] = false;
            m_released[sf::Keyboard::Key::RShift] = false;
            m_released[sf::Keyboard::Key::LControl] = false;
            m_released[sf::Keyboard::Key::RControl] = false;
            m_released[sf::Keyboard::Key::BackSpace] = false;

            m_released[sf::Keyboard::Key::F1] = false;
            m_released[sf::Keyboard::Key::F2] = false;
            m_released[sf::Keyboard::Key::F3] = false;
            m_released[sf::Keyboard::Key::F4] = false;
            m_released[sf::Keyboard::Key::F5] = false;
            m_released[sf::Keyboard::Key::F6] = false;
            m_released[sf::Keyboard::Key::F7] = false;
            m_released[sf::Keyboard::Key::F8] = false;
            m_released[sf::Keyboard::Key::F9] = false;
            m_released[sf::Keyboard::Key::F10] = false;
            m_released[sf::Keyboard::Key::F11] = false;
            m_released[sf::Keyboard::Key::F12] = false;

            m_released[sf::Keyboard::Key::Num0] = false;
            m_released[sf::Keyboard::Key::Num1] = false;
            m_released[sf::Keyboard::Key::Num2] = false;
            m_released[sf::Keyboard::Key::Num3] = false;
            m_released[sf::Keyboard::Key::Num4] = false;
            m_released[sf::Keyboard::Key::Num5] = false;
            m_released[sf::Keyboard::Key::Num6] = false;
            m_released[sf::Keyboard::Key::Num7] = false;
            m_released[sf::Keyboard::Key::Num8] = false;
            m_released[sf::Keyboard::Key::Num9] = false;

            m_released[sf::Keyboard::Key::Numpad0] = false;
            m_released[sf::Keyboard::Key::Numpad1] = false;
            m_released[sf::Keyboard::Key::Numpad2] = false;
            m_released[sf::Keyboard::Key::Numpad3] = false;
            m_released[sf::Keyboard::Key::Numpad4] = false;
            m_released[sf::Keyboard::Key::Numpad5] = false;
            m_released[sf::Keyboard::Key::Numpad6] = false;
            m_released[sf::Keyboard::Key::Numpad7] = false;
            m_released[sf::Keyboard::Key::Numpad8] = false;
            m_released[sf::Keyboard::Key::Numpad9] = false;

            m_mouseReleased[sf::Mouse::Button::Left] = false;
            m_mouseReleased[sf::Mouse::Button::Middle] = false;
            m_mouseReleased[sf::Mouse::Button::Right] = false;
            reset();
        }
    }
};

} // namespace JamTemplate

#endif
