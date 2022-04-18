#ifndef JAMTEMPLATE_INPUT_SET_INTERFACE_HPP
#define JAMTEMPLATE_INPUT_SET_INTERFACE_HPP

#include <input/mouse/mouse_interface.hpp>

namespace jt {

class InputSetInterface {
public:
    virtual ~InputSetInterface() = default;

    /// Update the input
    /// \param mp the mouse buttons
    virtual void update(
        bool shouldProcessKeys, bool shouldProcessMouse, MousePosition const& mp, float elapsed)
        = 0;

    /// Reset the input
    virtual void reset() = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_INPUT_SET_INTERFACE_HPP
