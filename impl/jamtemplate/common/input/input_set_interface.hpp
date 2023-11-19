#ifndef JAMTEMPLATE_INPUT_SET_INTERFACE_HPP
#define JAMTEMPLATE_INPUT_SET_INTERFACE_HPP

#include <input/mouse/mouse_interface.hpp>

namespace jt {

class InputSetInterface {
public:
    /// Update the input
    /// \param mp the mouse buttons
    virtual void update(
        bool shouldProcessKeys, bool shouldProcessMouse, MousePosition const& mp, float elapsed)
        = 0;

    /// Reset the input
    virtual void reset() = 0;

    virtual ~InputSetInterface() = default;

    // no copy, no move. Avoid slicing.
    InputSetInterface(InputSetInterface const&) = delete;
    InputSetInterface(InputSetInterface&&) = delete;
    InputSetInterface& operator=(InputSetInterface const&) = delete;
    InputSetInterface& operator=(InputSetInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    InputSetInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_INPUT_SET_INTERFACE_HPP
