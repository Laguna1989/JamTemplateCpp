#ifndef GUARD_JAMTEMPLATE_CONTROL_COMMAND_IMPL_HPP
#define GUARD_JAMTEMPLATE_CONTROL_COMMAND_IMPL_HPP

#include "control_command_interface.hpp"

class ControlCommandImpl : public jt::ControlCommandInterface {
public:
    void execute(float elapsed) override;
    void reset() override;

private:
    bool m_hasBeenExecutedAlready { false };
    virtual void doExecute(float elapsed) = 0
};

#endif // GUARD_JAMTEMPLATE_CONTROL_COMMAND_IMPL_HPP
