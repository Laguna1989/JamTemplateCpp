#ifndef GUARD_JAMTEMPLATE_COMMAND_RECORDER_HPP
#define GUARD_JAMTEMPLATE_COMMAND_RECORDER_HPP

#include "input/control_command_interface.hpp"

class CommandRecorder : public jt::ControlCommandInterface {
public:
    bool m_executed { false };
    bool m_reset { false };
    void execute(float elapsed) override;
    void reset() override;
};

#endif // GUARD_JAMTEMPLATE_COMMAND_RECORDER_HPP
