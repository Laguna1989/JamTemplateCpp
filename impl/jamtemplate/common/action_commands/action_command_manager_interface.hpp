#ifndef GUARD_JAMTEMPLATE_ACTION_COMMAND_MANAGER_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_ACTION_COMMAND_MANAGER_INTERFACE_HPP

#include <functional>
#include <memory>
#include <string>

namespace jt {
class ActionCommandManagerInterface {
public:
    using ActionCommandCallbackType = std::function<void(std::vector<std::string>)>;

    virtual ~ActionCommandManagerInterface() = default;

    virtual void executeCommand(std::string const& fullCommandString) = 0;

    ///
    /// \param commandName
    /// \param callback
    /// \return shared pointer to keep the commandName alive. If the user destroys the shared
    /// pointer, the commandName is automatically unregistered
    virtual std::shared_ptr<bool> registerTemporaryCommand(
        std::string const& commandName, ActionCommandCallbackType callback)
        = 0;

    virtual std::vector<std::string> getAllCommands() = 0;

    virtual void update() = 0;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_ACTION_COMMAND_MANAGER_INTERFACE_HPP
