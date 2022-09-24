#ifndef JAMTEMPLATE_KEYBOARDINPUT_HPP
#define JAMTEMPLATE_KEYBOARDINPUT_HPP

#include <input/control_commands/control_command_interface.hpp>
#include <input/input_manager_interface.hpp>
#include <keyboard_input_lib.hpp>
#include <functional>
#include <map>

namespace jt {

class KeyboardInput : public KeyboardInterface {
public:
    using KeyboardKeyCheckFunction = std::function<bool(jt::KeyCode)>;

    explicit KeyboardInput(
        KeyboardKeyCheckFunction checkFunc = [](auto k) { return libKeyValue(k); });

    virtual void updateKeys() override;

    virtual bool pressed(jt::KeyCode k) override;
    virtual bool released(jt::KeyCode k) override;

    virtual bool justPressed(jt::KeyCode k) override;
    virtual bool justReleased(jt::KeyCode k) override;

    void updateCommands(float elapsed) override;

    virtual void reset() override;

    void setCommandJustPressed(std::vector<KeyCode> const& keys,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandPressed(std::vector<KeyCode> const& keys,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandReleased(std::vector<KeyCode> const& keys,
        std::shared_ptr<jt::ControlCommandInterface> command) override;
    void setCommandJustReleased(std::vector<KeyCode> const& keys,
        std::shared_ptr<jt::ControlCommandInterface> command) override;

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

#endif
