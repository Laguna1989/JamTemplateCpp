#ifndef GUARD_JAMTEMPLATE_CONTROL_COMMAND_NULL_HPP
#define GUARD_JAMTEMPLATE_CONTROL_COMMAND_NULL_HPP

#include <input/control_commands/control_command_interface.hpp>

namespace jt {

class ControlCommandNull : public ControlCommandInterface {
public:
    void execute(float elapsed) override;
    void reset() override;
};
} // namespace jt
#endif // GUARD_JAMTEMPLATE_CONTROL_COMMAND_NULL_HPP
