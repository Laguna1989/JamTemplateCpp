#include "action_command_manager.hpp"
#include <strutils.hpp>
#include <system_helper.hpp>

jt::ActionCommandManager::ActionCommandManager(jt::LoggerInterface& logger)
    : m_logger { logger }
{
}

void jt::ActionCommandManager::executeCommand(std::string const& fullCommandString)
{
    if (fullCommandString.empty()) {
        return;
    }

    auto const splitCommand = strutil::split(strutil::trim_copy(fullCommandString), " ");
    auto const commandIdentifierString = splitCommand.at(0);
    auto const commandArguments = getArguments(splitCommand);

    auto const command_entry = std::find_if(m_registeredCommands.cbegin(),
        m_registeredCommands.cend(), [&commandIdentifierString](auto const& kvp) {
            auto const currentCommandToBeChecked = kvp.first;
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
    std::get<1>(command_entry->second)(commandArguments);
}

std::vector<std::string> jt::ActionCommandManager::getArguments(
    std::vector<std::string> const& args) const
{
    if (args.size() <= 1) {
        return {};
    }
    return std::vector<std::string> { args.cbegin() + 1, args.cend() };
}

void jt::ActionCommandManager::removeUnusedCommands()
{
    std::erase_if(m_registeredCommands, [this](auto const& kvp) {
        auto shared_state = std::get<0>(kvp.second);
        if (shared_state.expired()) {
            m_logger.info("remove command '" + kvp.first + "'");
            return true;
        }
        return false;
    });
}

std::shared_ptr<bool> jt::ActionCommandManager::registerTemporaryCommand(
    std::string const& commandName, ActionCommandCallbackType callback)
{
    std::shared_ptr<bool> sharedState = std::make_shared<bool>();

    std::string const trimmedCommand = strutil::trim_copy(commandName);
    m_registeredCommands[trimmedCommand]
        = std::make_tuple(std::weak_ptr<bool> { sharedState }, callback);
    m_logger.info("registered command '" + trimmedCommand + "'");
    return sharedState;
}

void jt::ActionCommandManager::update() { removeUnusedCommands(); }

std::vector<std::string> jt::ActionCommandManager::getAllCommands()
{
    std::vector<std::string> commands {};
    commands.resize(m_registeredCommands.size());
    for (auto& tpl : m_registeredCommands) {
        commands.push_back(tpl.first);
    }
    std::sort(commands.begin(), commands.end());
    return commands;
}
