﻿#ifndef GUARD_JAMTEMPLATE_MOUSEINPUT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_MOUSEINPUT_HPP_INCLUDEGUARD

#include "InputManagerInterface.hpp"
#include "MouseInputLib.hpp"
#include "Vector.hpp"
#include <functional>
#include <map>

namespace jt {

class MouseInput : public MouseInputInterface {
public:
    using MouseButtonCheckFunction = std::function<bool(jt::MouseButtonCode)>;
    MouseInput(MouseButtonCheckFunction checkFunction = [](auto b) { return libKeyValue(b); });
    virtual void updateMousePosition(MousePosition const& mp) override;
    virtual void updateButtons() override;

    virtual jt::Vector2 getMousePositionWorld() override;
    virtual jt::Vector2 getMousePositionScreen() override;

    virtual bool pressed(jt::MouseButtonCode b) override;
    virtual bool released(jt::MouseButtonCode b) override;

    virtual bool justPressed(jt::MouseButtonCode b) override;
    virtual bool justReleased(jt::MouseButtonCode b) override;

    virtual void reset() override;

private:
    MouseButtonCheckFunction m_checkFunction;
    std::map<jt::MouseButtonCode, bool> m_mousePressed;
    std::map<jt::MouseButtonCode, bool> m_mouseJustPressed;

    std::map<jt::MouseButtonCode, bool> m_mouseReleased;
    std::map<jt::MouseButtonCode, bool> m_mouseJustReleased;

    float m_mouseWorldX;
    float m_mouseWorldY;

    float m_mouseScreenX;
    float m_mouseScreenY;
};

} // namespace jt

#endif
