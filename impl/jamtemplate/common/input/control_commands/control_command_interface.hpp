#ifndef JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP
#define JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP

namespace jt {
class ControlCommandInterface {
public:
    virtual ~ControlCommandInterface() = default;
    virtual void execute(float elapsed) = 0;
    virtual void reset() = 0;
};

} // namespace jt
#endif // JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP
