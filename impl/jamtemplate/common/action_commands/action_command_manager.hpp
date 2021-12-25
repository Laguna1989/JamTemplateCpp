#ifndef MYAWESOMEGAME_ACTION_COMMAND_MANAGER_HPP
#define MYAWESOMEGAME_ACTION_COMMAND_MANAGER_HPP

#include "action_command_manager_interface.hpp"
#include "logging/logger_interface.hpp"
namespace jt {
class ActionCommandManager : public ActionCommandManagerInterface {
public:
    ActionCommandManager(LoggerInterface& logger);
    void executeCommand(std::string const& fullCommandString) override;

    std::shared_ptr<bool> registerTemporaryCommand(
        std::string const& commandName, ActionCommandCallbackType callback) override;
    void update() override;
    std::vector<std::string> getAllCommands() override;

private:
    jt::LoggerInterface& m_logger;
    std::vector<std::tuple<std::string, std::weak_ptr<bool>, ActionCommandCallbackType>>
        m_registeredCommands;
    void removeUnusedCommands();
    std::vector<std::string> getArguments(std::vector<std::string> const& args) const;
};
} // namespace jt

#endif // MYAWESOMEGAME_ACTION_COMMAND_MANAGER_HPP
