#ifndef GUARD_JAMTEMPLATE_TILEMAP_HELPERS_HPP
#define GUARD_JAMTEMPLATE_TILEMAP_HELPERS_HPP

#include "drawable_interface.hpp"
#include "info_rect.hpp"

namespace jt {
namespace tilemap {

std::shared_ptr<jt::DrawableInterface> createShapeFrom(InfoRect const& info);

}
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILEMAP_HELPERS_HPP
