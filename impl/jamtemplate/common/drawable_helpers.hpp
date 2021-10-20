#ifndef GUARD_JAMTEMPLATE_DRAWABLE_HELPER_GUARD_HPP
#define GUARD_JAMTEMPLATE_DRAWABLE_HELPER_GUARD_HPP

#include "color.hpp"
#include "render_target.hpp"
#include "sprite.hpp"
#include "vector.hpp"
#include <memory>
#include <string>

namespace jt {

// fwd declarations
class Shape;
class Text;

namespace dh {

std::shared_ptr<jt::Shape> createRectShape(
    jt::Vector2 size, jt::Color const& col = jt::colors::White);

std::shared_ptr<jt::Text> createText(std::weak_ptr<jt::renderTarget> rt, std::string const& text,
    unsigned int fontSize, jt::Color const& col = jt::colors::White,
    std::string const& font_path = "assets/font.ttf");

std::shared_ptr<jt::Sprite> createVignette(jt::Vector2 const& size);

} // namespace dh

} // namespace jt

#endif
