
#include "SmartDrawableHelpers.hpp"
#include "SmartShape.hpp"
#include "SmartText.hpp"

namespace jt {
namespace sdh {

std::shared_ptr<jt::SmartShape> createRectShape(jt::Vector2 size, jt::Color const& col)
{
    auto ptr = std::make_shared<jt::SmartShape>();
    ptr->makeRect(size);
    ptr->setColor(col);
    return ptr;
}

std::shared_ptr<jt::SmartText> createText(std::weak_ptr<jt::renderTarget> rt,
    std::string const& text, unsigned int fontSize, jt::Color const& col,
    std::string const& font_path)
{
    auto ptr = std::make_shared<jt::SmartText>();
    ptr->loadFont(font_path, fontSize, rt);
    ptr->setText(text);
    ptr->setColor(col);
    return ptr;
}

} // namespace sdh
} // namespace jt
