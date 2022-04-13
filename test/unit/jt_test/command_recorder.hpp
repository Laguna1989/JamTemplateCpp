#ifndef JAMTEMPLATE_COMMAND_RECORDER_HPP
#define JAMTEMPLATE_COMMAND_RECORDER_HPP

#include <input/control_commands/control_command_interface.hpp>

class CommandRecorder : public jt::ControlCommandInterface {
public:
    bool m_executed { false };
    bool m_reset { false };
    void execute(float elapsed) override;
    void reset() override;
};

#endif // JAMTEMPLATE_COMMAND_RECORDER_HPP
