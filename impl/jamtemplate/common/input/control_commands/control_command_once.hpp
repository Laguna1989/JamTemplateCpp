#pragma once

#include <input/control_commands/control_command_interface.hpp>

namespace jt {
class ControlCommandOnce : public jt::ControlCommandInterface {
public:
    void execute(float elapsed) override;
    void reset() override;

private:
    bool m_hasBeenExecutedAlready { false };
    virtual void doExecute(float elapsed) = 0;
};
} // namespace jt
