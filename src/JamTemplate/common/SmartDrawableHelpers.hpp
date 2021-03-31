#ifndef GUARD_JAMTEMPLATE_SMART_DRAWABLES_HELPER_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_SMART_DRAWABLES_HELPER_GUARD_HPP_12345

#include "Color.hpp"
#include "Rendertarget.hpp"
#include "Vector.hpp"
#include <memory>
#include <string>

namespace jt {

// fwd declarations
class SmartShape;
class SmartText;

namespace sdh {

std::shared_ptr<jt::SmartShape> createRectShape(
    jt::Vector2 size, jt::Color const& col = jt::colors::White);

std::shared_ptr<jt::SmartText> createText(std::weak_ptr<jt::renderTarget> rt,
    std::string const& text, unsigned int fontSize, jt::Color const& col = jt::colors::White,
    std::string const& font_path = "assets/font.ttf");

} // namespace sdh

} // namespace jt

#endif
