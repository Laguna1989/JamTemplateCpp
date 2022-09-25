#ifndef JAMTEMPLATE_ACTION_COMMAND_MANAGER_HPP
#define JAMTEMPLATE_ACTION_COMMAND_MANAGER_HPP

#include <action_commands/action_command_manager_interface.hpp>
#include <log/logger_interface.hpp>
#include <map>

namespace jt {
class ActionCommandManager : public ActionCommandManagerInterface {
public:
    explicit ActionCommandManager(LoggerInterface& logger);
    void executeCommand(std::string const& fullCommandString) override;

    std::shared_ptr<bool> registerTemporaryCommand(
        std::string const& commandName, ActionCommandCallbackType callback) override;
    void update() override;
    std::vector<std::string> getAllCommands() override;

private:
    jt::LoggerInterface& m_logger;
    std::map<std::string, std::tuple<std::weak_ptr<bool>, ActionCommandCallbackType>>
        m_registeredCommands;
    void removeUnusedCommands();
    std::vector<std::string> getArguments(std::vector<std::string> const& args) const;
};
} // namespace jt

#endif // JAMTEMPLATE_ACTION_COMMAND_MANAGER_HPP
