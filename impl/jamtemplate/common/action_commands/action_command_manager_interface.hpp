#ifndef JAMTEMPLATE_ACTION_COMMAND_MANAGER_INTERFACE_HPP
#define JAMTEMPLATE_ACTION_COMMAND_MANAGER_INTERFACE_HPP

#include <functional>
#include <memory>
#include <string>

namespace jt {
class ActionCommandManagerInterface {
public:
    using ActionCommandCallbackType = std::function<void(std::vector<std::string>)>;

    /// Execute a specific command string
    /// \param fullCommandString the command string to execute
    virtual void executeCommand(std::string const& fullCommandString) = 0;

    /// register a temporary command
    /// \param commandName the name under which the command is stored
    /// \param callback the callback for the command
    /// \return shared pointer to keep the commandName alive. If the user destroys the shared
    /// pointer, the commandName is automatically unregistered
    virtual std::shared_ptr<bool> registerTemporaryCommand(
        std::string const& commandName, ActionCommandCallbackType callback)
        = 0;

    /// Get a list of all registered commands
    /// \return a vector of all currently registered commands
    virtual std::vector<std::string> getAllCommands() = 0;

    /// update
    virtual void update() = 0;

    virtual ~ActionCommandManagerInterface() = default;

    // no copy, no move. Avoid slicing.
    ActionCommandManagerInterface(const ActionCommandManagerInterface&) = delete;
    ActionCommandManagerInterface(ActionCommandManagerInterface&&) = delete;
    ActionCommandManagerInterface& operator=(const ActionCommandManagerInterface&) = delete;
    ActionCommandManagerInterface& operator=(ActionCommandManagerInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    ActionCommandManagerInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_ACTION_COMMAND_MANAGER_INTERFACE_HPP
