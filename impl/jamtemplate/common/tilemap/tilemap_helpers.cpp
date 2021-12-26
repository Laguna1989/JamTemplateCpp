#include "tilemap_helpers.hpp"
#include "drawable_helpers.hpp"
#include "shape.hpp"

namespace jt {
namespace tilemap {

std::shared_ptr<jt::DrawableInterface> createShapeFrom(
    InfoRect const& info, jt::TextureManagerInterface& textureManager)
{
    std::shared_ptr<jt::Shape> shape
        = jt::dh::createShapeRect(info.size, jt::colors::White, textureManager);
    shape->setRotation(-info.rotation);
    shape->setPosition(info.position);
    shape->update(0.1f);

    return shape;
}
} // namespace tilemap
} // namespace jt
