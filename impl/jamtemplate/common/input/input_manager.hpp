#ifndef GUARD_JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD

#include "input_manager_interface.hpp"
#include <memory>

namespace jt {

class InputManager : public InputManagerInterface {
public:
    void update(MousePosition const& mp, float elapsed) override;
    InputManager(std::shared_ptr<MouseInputInterface> mouse,
        std::shared_ptr<KeyboardInputInterface> keyboard);
    virtual ~InputManager() = default;

    std::shared_ptr<MouseInputInterface> mouse() override;
    std::shared_ptr<KeyboardInputInterface> keyboard() override;
    void reset() override;

private:
    std::shared_ptr<MouseInputInterface> m_mouse { nullptr };
    std::shared_ptr<KeyboardInputInterface> m_keyboard { nullptr };
};

} // namespace jt

#endif
