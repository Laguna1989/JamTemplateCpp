#ifndef GUARD_JAMTEMAPLTE_INPUT_MANAGER_NULL_HPP
#define GUARD_JAMTEMAPLTE_INPUT_MANAGER_NULL_HPP

#include "input_manager_interface.hpp"

namespace jt {

class MouseInputNull : public MouseInputInterface {
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

class KeyboardInputNull : public KeyboardInputInterface {
public:
    void updateKeys() override;
    bool pressed(jt::KeyCode k) override;
    bool released(jt::KeyCode k) override;
    bool justPressed(jt::KeyCode k) override;
    bool justReleased(jt::KeyCode k) override;
    void reset() override;
};

class InputManagerNull : public InputManagerInterface {
public:
    std::shared_ptr<MouseInputInterface> mouse() override;
    std::shared_ptr<KeyboardInputInterface> keyboard() override;
    void update(MousePosition const& mp, float elapsed) override;
    void reset() override;
};
} // namespace jt
#endif // GUARD_JAMTEMAPLTE_INPUT_MANAGER_NULL_HPP
