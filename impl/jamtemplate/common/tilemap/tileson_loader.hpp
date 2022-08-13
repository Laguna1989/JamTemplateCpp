#ifndef JAMTEMPLATE_TILESON_LOADER_HPP
#define JAMTEMPLATE_TILESON_LOADER_HPP

#include <shape.hpp>
#include <sprite.hpp>
#include <texture_manager_interface.hpp>
#include <tilemap/info_rect.hpp>
#include <tilemap/tile_info.hpp>
#include <tilemap/tile_node.hpp>
#include <tilemap/tilemap_collisions.hpp>
#include <tilemap/tilemap_manager_tileson_impl.hpp>
#include <memory>
#include <tuple>

namespace jt {
namespace tilemap {

class TilesonLoader {
public:
    TilesonLoader(std::string const& fileName);

    std::vector<InfoRect> loadObjectsFromLayer(std::string const& layerName);

    std::vector<std::shared_ptr<TileNode>> loadTileNodesFromLayer(std::string const& layerName,
        jt::TextureManagerInterface& textureManager, bool dismissBlockedTiles = false);

    std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> loadNodesFromLayer(
        std::string const& layerName);

    std::tuple<std::vector<TileInfo>, std::vector<std::shared_ptr<jt::Sprite>>> loadTilesFromLayer(
        std::string const& layerName, jt::TextureManagerInterface& textureManager);

    TilemapCollisions loadCollisionsFromLayer(std::string const& layerName);

private:
    TilemapManagerTilesonImpl m_tilemapManager;
    std::string m_fileName;
};

} // namespace tilemap
} // namespace jt

#endif // JAMTEMPLATE_TILESON_LOADER_HPP
