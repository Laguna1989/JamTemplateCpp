#ifndef GUARD_JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP

namespace jt {
class ControlCommandInterface {
    virtual ~ControlCommandInterface() = default;
    virtual void execute() = 0;
};

} // namespace jt
#endif // GUARD_JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP
