#ifndef GUARD_JAMTEMPLATE_TILESON_LOADER_HPP
#define GUARD_JAMTEMPLATE_TILESON_LOADER_HPP

#include "info_rect.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "texture_manager_interface.hpp"
#include "tile_info.hpp"
#include "tile_node.hpp"
#include "tilemap_collisions.hpp"
#include "tilemap_manager_tileson_impl.hpp"
#include <memory>
#include <tuple>

namespace jt {
namespace tilemap {

class TilesonLoader {
public:
    TilesonLoader(std::string const& fileName);

    std::vector<InfoRect> loadObjectsFromLayer(std::string const& layerName);

    std::vector<std::shared_ptr<TileNode>> loadNodesFromLayer(
        std::string const& layerName, jt::TextureManagerInterface& textureManager);

    std::tuple<std::vector<TileInfo>, std::vector<std::shared_ptr<jt::Sprite>>> loadTilesFromLayer(
        std::string const& layerName, jt::TextureManagerInterface& textureManager);

    TilemapCollisions loadCollisionsFromLayer(std::string const& layerName);

private:
    TilemapManagerTilesonImpl m_tilemapManager;
    std::string m_fileName;
};

} // namespace tilemap
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILESON_LOADER_HPP
