#ifndef JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP
#define JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP

namespace jt {
class ControlCommandInterface {
public:
    /// execute a control command
    /// \param elapsed elapsed time in seconds
    virtual void execute(float elapsed) = 0;
    /// reset the control command
    virtual void reset() = 0;

    virtual ~ControlCommandInterface() = default;

    // no copy, no move. Avoid slicing.
    ControlCommandInterface(ControlCommandInterface const&) = delete;
    ControlCommandInterface(ControlCommandInterface&&) = delete;
    ControlCommandInterface& operator=(ControlCommandInterface const&) = delete;
    ControlCommandInterface& operator=(ControlCommandInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    ControlCommandInterface() = default;
};

} // namespace jt
#endif // JAMTEMPLATE_CONTROL_COMMAND_INTERFACE_HPP
