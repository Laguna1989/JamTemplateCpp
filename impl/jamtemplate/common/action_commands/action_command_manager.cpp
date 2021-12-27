#include "action_command_manager.hpp"
#include "strutils.hpp"

namespace jt {

ActionCommandManager::ActionCommandManager(LoggerInterface& logger)
    : m_logger { logger }
{
}

void ActionCommandManager::executeCommand(std::string const& fullCommandString)
{
    if (fullCommandString.empty()) {
        return;
    }

    auto const splitCommand = strutil::split(strutil::trim_copy(fullCommandString), " ");
    auto const commandIdentifierString = splitCommand.at(0);
    auto const commandArguments = getArguments(splitCommand);

    auto const command_entry = std::find_if(m_registeredCommands.cbegin(),
        m_registeredCommands.cend(), [&commandIdentifierString](auto const& c) {
            auto const currentCommandToBeChecked = std::get<0>(c);
            if (commandIdentifierString == currentCommandToBeChecked) {
                // If weird behaviour occurs, add a check if shared state is still alive here.
                return true;
            }
            return false;
        });
    if (command_entry == m_registeredCommands.end()) {
        m_logger.error("unknown commandIdentifierString '" + fullCommandString + "'");
        return;
    }
    // perform the actual action command call
    std::get<2> (*command_entry)(commandArguments);
}

std::vector<std::string> ActionCommandManager::getArguments(
    std::vector<std::string> const& args) const
{
    if (args.size() <= 1) {
        return {};
    }
    return std::vector<std::string> { args.cbegin() + 1, args.cend() };
}

void ActionCommandManager::removeUnusedCommands()
{
    m_registeredCommands.erase(
        std::remove_if(m_registeredCommands.begin(), m_registeredCommands.end(),
            [this](auto const& tpl) {
                auto shared_state = std::get<1>(tpl);
                if (shared_state.expired()) {
                    m_logger.info("remove command '" + std::get<0>(tpl) + "'");
                    return true;
                }
                return false;
            }),
        m_registeredCommands.end());
}

std::shared_ptr<bool> ActionCommandManager::registerTemporaryCommand(
    std::string const& commandName, ActionCommandCallbackType callback)
{
    std::shared_ptr<bool> sharedState = std::make_shared<bool>();

    std::string const trimmedCommand = strutil::trim_copy(commandName);
    m_registeredCommands.emplace_back(
        std::make_tuple(trimmedCommand, std::weak_ptr<bool> { sharedState }, callback));
    m_logger.info("registered command '" + trimmedCommand + "'");
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
