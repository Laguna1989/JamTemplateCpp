#ifndef JAMTEMPLATE_KEYBOARD_INPUT_NULL_HPP
#define JAMTEMPLATE_KEYBOARD_INPUT_NULL_HPP

#include <input/keyboard/keyboard_interface.hpp>
namespace jt {

class KeyboardInputNull : public KeyboardInterface {
public:
    void updateKeys() override;
    bool pressed(jt::KeyCode k) override;
    bool released(jt::KeyCode k) override;
    bool justPressed(jt::KeyCode k) override;
    bool justReleased(jt::KeyCode k) override;
    void reset() override;
    void setCommandJustPressed(std::vector<KeyCode> const& key,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandPressed(std::vector<KeyCode> const& key,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandReleased(std::vector<KeyCode> const& key,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandJustReleased(std::vector<KeyCode> const& key,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void updateCommands(float elapsed) override;
};

} // namespace jt

#endif // JAMTEMPLATE_KEYBOARD_INPUT_NULL_HPP
