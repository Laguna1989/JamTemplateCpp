#ifndef GUARD_JAMTEMPLATE_CONTROL_COMMAND_NULL_HPP
#define GUARD_JAMTEMPLATE_CONTROL_COMMAND_NULL_HPP

#include "control_command_interface.hpp"

namespace jt {

class ControlCommandNull : public ControlCommandInterface {
    void execute(float elapsed) override;

public:
    void reset() override;
};
} // namespace jt
#endif // GUARD_JAMTEMPLATE_CONTROL_COMMAND_NULL_HPP
