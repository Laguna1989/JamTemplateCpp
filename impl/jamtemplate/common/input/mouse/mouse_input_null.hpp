#ifndef GUARD_JAMTEMPLATE_MOUSE_INPUT_NULL_HPP
#define GUARD_JAMTEMPLATE_MOUSE_INPUT_NULL_HPP

#include "mouse_interface.hpp"

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

#endif // GUARD_JAMTEMPLATE_MOUSE_INPUT_NULL_HPP
