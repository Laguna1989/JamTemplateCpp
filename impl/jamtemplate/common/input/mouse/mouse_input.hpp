#ifndef JAMTEMPLATE_MOUSEINPUT_HPP
#define JAMTEMPLATE_MOUSEINPUT_HPP

#include <input/mouse/mouse_defines.hpp>
#include <input/mouse/mouse_interface.hpp>
#include <mouse_input_lib.hpp>
#include <functional>
#include <map>

namespace jt {

class MouseInput : public MouseInterface {
public:
    using MouseButtonCheckFunction = std::function<bool(jt::MouseButtonCode)>;

    explicit MouseInput(
        MouseButtonCheckFunction checkFunction = [](auto b) { return libKeyValue(b); });

    virtual void updateMousePosition(MousePosition const& mp) override;
    virtual void updateButtons() override;

    virtual jt::Vector2f getMousePositionWorld() override;
    virtual jt::Vector2f getMousePositionScreen() override;

    virtual bool pressed(jt::MouseButtonCode b) override;
    virtual bool released(jt::MouseButtonCode b) override;

    virtual bool justPressed(jt::MouseButtonCode b) override;
    virtual bool justReleased(jt::MouseButtonCode b) override;

    virtual void reset() override;

private:
    MouseButtonCheckFunction m_checkFunction;
    std::map<jt::MouseButtonCode, bool> m_mousePressed {};
    std::map<jt::MouseButtonCode, bool> m_mouseJustPressed {};

    std::map<jt::MouseButtonCode, bool> m_mouseReleased {};
    std::map<jt::MouseButtonCode, bool> m_mouseJustReleased {};

    float m_mouseWorldX { 0.0f };
    float m_mouseWorldY { 0.0f };

    float m_mouseScreenX { 0.0f };
    float m_mouseScreenY { 0.0f };
};

} // namespace jt

#endif
