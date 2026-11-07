#pragma once

#include <input/control_commands/control_command_interface.hpp>
#include <memory>
#include <vector>

namespace jt {

class ControlCommandComposite : public jt::ControlCommandInterface {
public:
    explicit ControlCommandComposite(
        std::vector<std::shared_ptr<jt::ControlCommandInterface>> const& commands);

    void execute(float elapsed) override;
    void reset() override;

private:
    std::vector<std::shared_ptr<jt::ControlCommandInterface>> m_commands;
};

} // namespace jt
