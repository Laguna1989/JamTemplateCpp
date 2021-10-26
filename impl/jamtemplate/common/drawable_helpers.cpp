
#include "drawable_helpers.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "text.hpp"

namespace jt {
namespace dh {

std::shared_ptr<jt::Shape> createRectShape(jt::Vector2 const& size, jt::Color const& col)
{
    auto ptr = std::make_shared<jt::Shape>();
    ptr->makeRect(size);
    ptr->setColor(col);
    return ptr;
}

std::shared_ptr<jt::Text> createText(std::weak_ptr<jt::renderTarget> rt, std::string const& text,
    unsigned int fontSize, jt::Color const& col, std::string const& font_path)
{
    auto ptr = std::make_shared<jt::Text>();
    ptr->loadFont(font_path, fontSize, std::move(rt));
    ptr->setText(text);
    ptr->setColor(col);
    return ptr;
}

std::shared_ptr<jt::Sprite> createVignette(jt::Vector2 const& size)
{
    auto ptr = std::make_shared<jt::Sprite>();
    ptr = std::make_shared<jt::Sprite>();
    ptr->loadSprite("#v#" + std::to_string(static_cast<int>(size.x())) + "#"
        + std::to_string(static_cast<int>(size.y())));
    ptr->setIgnoreCamMovement(true);
    return ptr;
}

} // namespace dh
} // namespace jt
