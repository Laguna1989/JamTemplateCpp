#ifndef GUARD_JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD

#include "input_manager_interface.hpp"
#include <memory>

namespace jt {

class InputManager : public InputManagerInterface {
public:
    void update(MousePosition const& mp, float elapsed) override;
    InputManager(std::shared_ptr<jt::MouseInputInterface> mouse,
        std::shared_ptr<jt::KeyboardInputInterface> keyboard,
        std::vector<std::shared_ptr<jt::GamepadInputInterface>> gamepads);
    virtual ~InputManager() = default;

    std::shared_ptr<MouseInputInterface> mouse() override;
    std::shared_ptr<KeyboardInputInterface> keyboard() override;
    std::shared_ptr<GamepadInputInterface> gamepad(int gamepad_id) override;
    size_t getNumberOfGamepads() const override;
    void reset() override;

private:
    std::shared_ptr<MouseInputInterface> m_mouse { nullptr };
    std::shared_ptr<KeyboardInputInterface> m_keyboard { nullptr };
    std::vector<std::shared_ptr<GamepadInputInterface>> m_gamepads {};
};

} // namespace jt

#endif
