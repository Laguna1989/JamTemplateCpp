#ifndef GUARD_JAMTEMPLATE_TILEMAP_GENERATOR_HPP
#define GUARD_JAMTEMPLATE_TILEMAP_GENERATOR_HPP

#include "sprite.hpp"
#include "texture_manager_interface.hpp"
#include "tile_info.hpp"
#include <vector>

namespace jt {
namespace tilemap {

class TilemapGenerator {
public:
    std::tuple<std::vector<TileInfo>, std::vector<jt::Sprite>> createRandomMap(
        std::string const& layerName, std::shared_ptr<jt::TextureManagerInterface> textureManager);
};

} // namespace tilemap
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILEMAP_GENERATOR_HPP
