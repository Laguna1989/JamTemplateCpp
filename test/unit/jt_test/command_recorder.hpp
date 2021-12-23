#ifndef MYAWESOMEGAME_COMMAND_RECORDER_HPP
#define MYAWESOMEGAME_COMMAND_RECORDER_HPP

#include "input/control_command_interface.hpp"

class CommandRecorder : public jt::ControlCommandInterface {
public:
    bool m_executed { false };
    bool m_reset { false };
    void execute(float elapsed) override;
    void reset() override;
};

#endif // MYAWESOMEGAME_COMMAND_RECORDER_HPP
