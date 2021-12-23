#include "control_command_composite.hpp"

namespace jt {

ControlCommandComposite::ControlCommandComposite(
    std::vector<std::shared_ptr<ControlCommandInterface>> const& commands)
    : m_commands { commands }
{
}

void ControlCommandComposite::execute(float elapsed)
{
    for (auto& command : m_commands) {
        command->execute(elapsed);
    }
}

void ControlCommandComposite::reset()
{
    for (auto& command : m_commands) {
        command->reset();
    }
}

} // namespace jt
