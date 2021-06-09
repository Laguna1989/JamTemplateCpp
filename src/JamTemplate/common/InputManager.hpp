#ifndef GUARD_JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_INPUTMANAGER_HPP_INCLUDEGUARD

#include "InputManagerInterface.hpp"
#include <memory>

namespace jt {

class InputManager : public InputManagerInterface {
public:
    InputManager(std::shared_ptr<MouseInputInterface> mouse,
        std::shared_ptr<KeyboardInputInterface> keyboard);

    std::shared_ptr<MouseInputInterface> mouse() override;
    std::shared_ptr<KeyboardInputInterface> keyboard() override;
    void reset() override;

private:
    std::shared_ptr<MouseInputInterface> m_mouse;
    std::shared_ptr<KeyboardInputInterface> m_keyboard;
};

} // namespace jt

#endif
