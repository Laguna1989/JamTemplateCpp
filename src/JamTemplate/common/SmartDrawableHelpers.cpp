
#include "SmartDrawableHelpers.hpp"
#include "SmartShape.hpp"

namespace jt {
namespace sdh {

std::shared_ptr<jt::SmartShape> createRectShape(jt::Vector2 size, jt::Color const& col)
{
    auto ptr = std::make_shared<jt::SmartShape>();
    ptr->makeRect(size);
    ptr->setColor(col);
    return ptr;
}

} // namespace sdh
} // namespace jt
