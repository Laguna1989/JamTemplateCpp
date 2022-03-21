#include "control_command_composite.hpp"

jt::ControlCommandComposite::ControlCommandComposite(
    std::vector<std::shared_ptr<jt::ControlCommandInterface>> const& commands)
    : m_commands { commands }
{
}

void jt::ControlCommandComposite::execute(float elapsed)
{
    for (auto& command : m_commands) {
        command->execute(elapsed);
    }
}

void jt::ControlCommandComposite::reset()
{
    for (auto& command : m_commands) {
        command->reset();
    }
}
