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

/// Create a rectangular shape
/// \param size the size of the shape (full length of the rectangle)
/// \param col the color of the shape
/// \return shared pointer to shape
std::shared_ptr<jt::Shape> createShapeRect(
    jt::Vector2f const& size, jt::Color const& col, jt::TextureManagerInterface& textureManager);

std::shared_ptr<jt::Shape> createShapeCircle(
    float radius, jt::Color const& col, jt::TextureManagerInterface& textureManager);

/// Create a text
/// \param renderTarget weak pointer to rendertarget
/// \param text the string displayed in the text
/// \param fontSize how big are the letters in the text
/// \param col the color of the text
/// \param font_path path to the ttf file (e.g. "assets/font.ttf")
/// \return shared pointer to text
std::shared_ptr<jt::Text> createText(std::weak_ptr<jt::RenderTarget> renderTarget,
    std::string const& text, unsigned int fontSize, jt::Color const& col = jt::colors::White,
    std::string const& font_path = "assets/font.ttf");

/// Create a vignette sprite
/// \param size the size of the vignette
/// \return shared pointer to sprite
std::shared_ptr<jt::Sprite> createVignette(
    jt::Vector2f const& size, jt::TextureManagerInterface& textureManager);

} // namespace dh

} // namespace jt

#endif
