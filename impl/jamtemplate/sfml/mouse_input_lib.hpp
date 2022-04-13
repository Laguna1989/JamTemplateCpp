#ifndef JAMTEMPLATE_MOUSEINPUTLIB_HPP
#define JAMTEMPLATE_MOUSEINPUTLIB_HPP

#include <input/mouse/mouse_defines.hpp>

namespace jt {

/// Helper function to ask for the state of a mouse button
/// \param b the button to check
/// \return true if button is pressed, false otherwise
bool libKeyValue(jt::MouseButtonCode b);

} // namespace jt
#endif
