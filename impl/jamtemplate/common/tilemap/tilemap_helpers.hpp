#ifndef GUARD_JAMTEMPLATE_TILEMAP_HELPERS_HPP
#define GUARD_JAMTEMPLATE_TILEMAP_HELPERS_HPP

#include "drawable_interface.hpp"
#include "info_rect.hpp"
#include "texture_manager_interface.hpp"

namespace jt {
namespace tilemap {

std::shared_ptr<jt::DrawableInterface> createShapeFrom(
    InfoRect const& info, jt::TextureManagerInterface& textureManager);

}
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILEMAP_HELPERS_HPP
