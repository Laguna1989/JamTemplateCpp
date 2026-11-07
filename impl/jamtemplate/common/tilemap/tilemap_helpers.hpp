#pragma once

#include <graphics/drawable_interface.hpp>
#include <texture_manager_interface.hpp>
#include <tilemap/info_rect.hpp>

namespace jt {
namespace tilemap {

std::shared_ptr<jt::DrawableInterface> createShapeFrom(
    InfoRect const& info, jt::TextureManagerInterface& textureManager);

}
} // namespace jt
