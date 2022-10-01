#ifndef JAMTEMPLATE_TILESON_LOADER_HPP
#define JAMTEMPLATE_TILESON_LOADER_HPP

#include <shape.hpp>
#include <sprite.hpp>
#include <texture_manager_interface.hpp>
#include <tilemap/info_rect.hpp>
#include <tilemap/tile_info.hpp>
#include <tilemap/tile_node.hpp>
#include <tilemap/tilemap_cache_interface.hpp>
#include <tilemap/tilemap_collisions.hpp>
#include <memory>
#include <tuple>

namespace jt {
namespace tilemap {

class TilesonLoader {
public:
    /// Tileson loader Constructor
    /// \param cache the cache to be used (to avoid duplicate loading of the same json
    /// \param fileName the filename of the json file to be loaded
    TilesonLoader(jt::TilemapCacheInterface& cache, std::string const& fileName);

    /// Load Objects from layer. Can directly be used to construct an ObjectLayer.
    /// \param layerName the name of the object layer
    /// \return Vector of InfoRects containing information about the objects
    std::vector<InfoRect> loadObjectsFromLayer(std::string const& layerName);

    /// Load TileNodes from Layer. Can be used to construct a NodeLayer
    /// \param layerName the name of the tile layer
    /// \param textureManager the texture manager
    /// \param dismissBlockedTiles true if blocked tiles should not be part of the returned vector
    /// at all
    /// \return the vector of TileNodes
    std::vector<std::shared_ptr<TileNode>> loadTileNodesFromLayer(std::string const& layerName,
        jt::TextureManagerInterface& textureManager, bool dismissBlockedTiles = false);

    /// Load NodeInterfaces from Layer (for pathfinding)
    /// \param layerName the name of the tile layer
    /// \return the vector of NodeInterfaces
    std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> loadNodesFromLayer(
        std::string const& layerName);

    /// Load Tiles from Layer. Can be used to construct a TileLayer.
    /// \param layerName the name of the tile layer.
    /// \param textureManager the texture manager
    /// \param tilesetPathPrefix the path where to look for the tileset image.
    /// \return tuple of vectors for TileInfo and Sprites
    std::tuple<std::vector<TileInfo>, std::vector<std::shared_ptr<jt::Sprite>>> loadTilesFromLayer(
        std::string const& layerName, jt::TextureManagerInterface& textureManager,
        std::string const& tilesetPathPrefix = "assets/");

    /// Load Collisions from layer. Will directly return a Tilemap Collision. Note: You most likely
    /// want to call refineCollisions() on the returned object.
    /// \param layerName the name of the tile layer
    /// \return the Tilmap Collisions
    TilemapCollisions loadCollisionsFromLayer(std::string const& layerName);

    /// Get the size of the map.
    /// \return the size of the map in tiles.
    jt::Vector2u getMapSizeInTiles() const;

private:
    TilemapCacheInterface& m_tilemapCache;
    std::string m_fileName;
};

} // namespace tilemap
} // namespace jt

#endif // JAMTEMPLATE_TILESON_LOADER_HPP
