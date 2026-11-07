#pragma once

#include <graphics/drawable_interface.hpp>
#include <memory>

namespace jt {

/// wrap drawable on screen.
/// \param drawable
void wrapOnScreen(jt::DrawableInterface& drawable, float margin = 10.0f);

} // namespace jt
