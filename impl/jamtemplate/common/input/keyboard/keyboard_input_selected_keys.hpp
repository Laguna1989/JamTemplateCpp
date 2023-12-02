#ifndef JAMTEMPLATE_KEYBOARD_INPUT_SELECTED_KEYS_HPP
#define JAMTEMPLATE_KEYBOARD_INPUT_SELECTED_KEYS_HPP

#include <input/keyboard/keyboard_interface.hpp>
#include <keyboard_input_lib.hpp>
#include <functional>
#include <map>

namespace jt {

/// Keyboard input that only listens for selected Keys. Key can be added via
/// listenForKey(jt::KeyCode).
class KeyboardInputSelectedKeys : public jt::KeyboardInterface {
public:
    using KeyboardKeyCheckFunction = std::function<bool(jt::KeyCode)>;

    explicit KeyboardInputSelectedKeys(
        KeyboardKeyCheckFunction checkFunc = [](auto k) { return libKeyValue(k); });

    /// Listen for a specific key
    /// \param k keycode
    void listenForKey(jt::KeyCode k);

    void updateKeys() override;
    bool pressed(jt::KeyCode k) override;
    bool released(jt::KeyCode k) override;
    bool justPressed(jt::KeyCode k) override;
    bool justReleased(jt::KeyCode k) override;
    void reset() override;
    void setCommandJustPressed(std::vector<KeyCode> const& keys,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandPressed(std::vector<KeyCode> const& keys,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandReleased(std::vector<KeyCode> const& keys,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandJustReleased(std::vector<KeyCode> const& keys,
        std::shared_ptr<jt::ControlCommandInterface> command) override;

    void updateCommands(float elapsed) override;

private:
    KeyboardKeyCheckFunction m_checkFunc;

    std::map<jt::KeyCode, bool> m_pressed {};
    std::map<jt::KeyCode, bool> m_released {};

    std::map<jt::KeyCode, bool> m_justPressed {};
    std::map<jt::KeyCode, bool> m_justReleased {};

    std::map<jt::KeyCode, std::shared_ptr<jt::ControlCommandInterface>> m_commandsPressed;
    std::map<jt::KeyCode, std::shared_ptr<jt::ControlCommandInterface>> m_commandsReleased;
    std::map<jt::KeyCode, std::shared_ptr<jt::ControlCommandInterface>> m_commandsJustPressed;
    std::map<jt::KeyCode, std::shared_ptr<jt::ControlCommandInterface>> m_commandsJustReleased;
};

} // namespace jt

#endif // JAMTEMPLATE_KEYBOARD_INPUT_SELECTED_KEYS_HPP
