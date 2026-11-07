#pragma once

#include <input/mouse/mouse_interface.hpp>

namespace jt {

class MouseInputNull : public MouseInterface {
public:
    void updateMousePosition(MousePosition const& mousePosition) override;
    void updateButtons() override;
    jt::Vector2f getMousePositionWorld() override;
    jt::Vector2f getMousePositionScreen() override;
    bool pressed(jt::MouseButtonCode b) override;
    bool released(jt::MouseButtonCode b) override;
    bool justPressed(jt::MouseButtonCode b) override;
    bool justReleased(jt::MouseButtonCode b) override;
    void reset() override;
};

} // namespace jt
