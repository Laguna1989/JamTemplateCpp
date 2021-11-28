#ifndef GUARD_JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP

namespace jt {
class ControlCommandInterface {
public:
    virtual ~ControlCommandInterface() = default;
    virtual void execute(float elapsed) = 0;
    virtual void reset() = 0;
};

} // namespace jt
#endif // GUARD_JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP
