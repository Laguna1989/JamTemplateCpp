#ifndef JAMTEMPLATE_INPUT_MANAGER_NULL_HPP
#define JAMTEMPLATE_INPUT_MANAGER_NULL_HPP

#include <input/input_manager_interface.hpp>

namespace jt {

class InputManagerNull : public InputManagerInterface {
public:
    std::shared_ptr<MouseInterface> mouse() override;
    std::shared_ptr<KeyboardInterface> keyboard() override;
    void update(MousePosition const& mp, float elapsed) override;
    void reset() override;
    std::shared_ptr<GamepadInterface> gamepad(int gamepad_id) override;
    size_t getNumberOfGamepads() const override;
};
} // namespace jt
#endif // JAMTEMPLATE_INPUT_MANAGER_NULL_HPP
