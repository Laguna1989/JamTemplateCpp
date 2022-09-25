#ifndef JAMTEMPLATE_INPUTMANAGER_HPP
#define JAMTEMPLATE_INPUTMANAGER_HPP

#include <input/input_manager_interface.hpp>
#include <memory>

namespace jt {

class InputManager : public InputManagerInterface {
public:
    explicit InputManager(std::shared_ptr<jt::MouseInterface> mouse = nullptr,
        std::shared_ptr<jt::KeyboardInterface> keyboard = nullptr,
        std::vector<std::shared_ptr<jt::GamepadInterface>> const& gamepads = {});
    virtual ~InputManager() = default;

    void update(bool shouldProcessKeys, bool shouldProcessMouse, MousePosition const& mp,
        float elapsed) override;

    std::shared_ptr<MouseInterface> mouse() override;
    std::shared_ptr<jt::KeyboardInterface> keyboard() override;
    std::shared_ptr<GamepadInterface> gamepad(int gamepad_id) override;
    size_t getNumberOfGamepads() const override;
    void reset() override;

private:
    std::shared_ptr<MouseInterface> m_mouse { nullptr };
    std::shared_ptr<KeyboardInterface> m_keyboard { nullptr };
    std::vector<std::shared_ptr<GamepadInterface>> m_gamepads {};
};

} // namespace jt

#endif
