#ifndef GUARD_JAMTEMPLATE_MOUSEINPUTLIB_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_MOUSEINPUTLIB_HPP_INCLUDEGUARD

#include "input/key_codes.hpp"

namespace jt {

/// Helper function to ask for the state of a mouse button
/// \param b the button to check
/// \return true if button is pressed, false otherwise
bool libKeyValue(jt::MouseButtonCode b);

} // namespace jt
#endif
