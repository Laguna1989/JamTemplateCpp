#include "action_command_manager.hpp"
#include "strutils.hpp"

namespace jt {

ActionCommandManager::ActionCommandManager(std::shared_ptr<jt::LoggerInterface> logger)
{
    m_logger = logger;
}

void ActionCommandManager::executeCommand(std::string const& fullCommandString)
{
    if (fullCommandString.empty()) {
        return;
    }

    removeUnusedCommands();

    for (auto& c : m_registeredCommands) {
        auto commandString = std::get<0>(c);

        if (fullCommandString == commandString) {
            auto shared_state = std::get<1>(c);
            if (shared_state.expired()) {
                continue;
            }
            std::get<2>(c)(fullCommandString);
            return;
        }
    }
    m_logger.lock()->error("unknown command '" + fullCommandString + "'");
}
void ActionCommandManager::removeUnusedCommands()
{
    m_registeredCommands.erase(
        std::remove_if(m_registeredCommands.begin(), m_registeredCommands.end(),
            [this](auto const& tpl) {
                auto shared_state = std::get<1>(tpl);
                if (shared_state.expired()) {
                    m_logger.lock()->info("remove command '" + std::get<0>(tpl) + "'");
                    return true;
                }
                return false;
            }),
        m_registeredCommands.end());
}

std::shared_ptr<bool> ActionCommandManager::registerTemporaryCommand(
    std::string const& commandName, std::function<void(std::string)> callback)
{
    std::shared_ptr<bool> sharedState = std::make_shared<bool>();

    std::string const trimmedCommand = strutil::trim_copy(commandName);
    m_registeredCommands.emplace_back(
        std::make_tuple(trimmedCommand, std::weak_ptr<bool> { sharedState }, callback));
    m_logger.lock()->info("registered command '" + trimmedCommand + "'");
    return sharedState;
}
void ActionCommandManager::update() { removeUnusedCommands(); }

std::vector<std::string> ActionCommandManager::getAllCommands()
{
    std::vector<std::string> commands;
    for (auto& tpl : m_registeredCommands) {
        commands.push_back(std::get<0>(tpl));
    }
    std::sort(commands.begin(), commands.end());
    return commands;
}

} // namespace jt
