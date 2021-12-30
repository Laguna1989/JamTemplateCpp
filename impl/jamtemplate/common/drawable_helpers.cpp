#include "drawable_helpers.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "text.hpp"

namespace jt {
namespace dh {

std::shared_ptr<jt::Shape> createShapeRect(
    jt::Vector2f const& size, jt::Color const& col, jt::TextureManagerInterface& textureManager)
{
    auto ptr = std::make_shared<jt::Shape>();
    ptr->makeRect(size, textureManager);
    ptr->setColor(col);
    return ptr;
}

std::shared_ptr<jt::Shape> createShapeCircle(
    float radius, Color const& col, jt::TextureManagerInterface& textureManager)
{
    auto ptr = std::make_shared<jt::Shape>();
    ptr->makeCircle(radius, textureManager);
    ptr->setColor(col);
    return ptr;
}

std::shared_ptr<jt::Text> createText(std::weak_ptr<jt::RenderTarget> renderTarget,
    std::string const& text, unsigned int fontSize, jt::Color const& col,
    std::string const& font_path)
{
    auto ptr = std::make_shared<jt::Text>();
    ptr->loadFont(font_path, fontSize, std::move(renderTarget));
    ptr->setText(text);
    ptr->setColor(col);
    return ptr;
}

std::shared_ptr<jt::Sprite> createVignette(
    jt::Vector2f const& size, jt::TextureManagerInterface& textureManager)
{
    auto ptr = std::make_shared<jt::Sprite>("#v#" + std::to_string(static_cast<int>(size.x)) + "#"
            + std::to_string(static_cast<int>(size.y)),
        textureManager);
    ptr->setIgnoreCamMovement(true);
    return ptr;
}

} // namespace dh
} // namespace jt
