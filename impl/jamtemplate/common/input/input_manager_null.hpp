#ifndef JAMTEMPLATE_INPUT_MANAGER_NULL_HPP
#define JAMTEMPLATE_INPUT_MANAGER_NULL_HPP

#include <input/input_manager_interface.hpp>

namespace jt {

class InputManagerNull : public InputManagerInterface {
public:
    InputManagerNull();
    std::shared_ptr<MouseInterface> mouse() override;
    std::shared_ptr<jt::KeyboardInterface> keyboard() override;
    void update(bool shouldProcessKeys, bool shouldProcessMouse, MousePosition const& mp,
        float elapsed) override;
    void reset() override;
    std::shared_ptr<GamepadInterface> gamepad(int gamepad_id) override;
    size_t getNumberOfGamepads() const override;

private:
    std::shared_ptr<MouseInterface> m_mouse { nullptr };
    std::shared_ptr<KeyboardInterface> m_keyboard { nullptr };
    std::shared_ptr<GamepadInterface> m_gamepad { nullptr };
};
} // namespace jt
#endif // JAMTEMPLATE_INPUT_MANAGER_NULL_HPP
