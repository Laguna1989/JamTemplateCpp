#ifndef JAMTEMPLATE_SCREEN_WRAP_HPP
#define JAMTEMPLATE_SCREEN_WRAP_HPP

#include <graphics/drawable_interface.hpp>
#include <memory>

namespace jt {

/// wrap drawable on screen.
/// \param drawable
void wrapOnScreen(jt::DrawableInterface& drawable, float margin = 10.0f);

} // namespace jt

#endif // JAMTEMPLATE_SCREEN_WRAP_HPP
