#ifndef GUARD_JAMTEMPLATE_NODELAYER_HPP
#define GUARD_JAMTEMPLATE_NODELAYER_HPP

#include "texture_manager_interface.hpp"
#include "tile_node.hpp"
#include "tileson.h"
#include <map>
#include <memory>
#include <vector>

namespace jt {
namespace tilemap {

class NodeLayer {
public:
    NodeLayer(std::string const& path, std::string const& layerName,
        std::shared_ptr<jt::TextureManagerInterface> textureManager);

    using Sptr = std::shared_ptr<NodeLayer>;
    std::shared_ptr<TileNode> getTileAt(unsigned int x, unsigned int y);
    std::vector<std::shared_ptr<TileNode>> getAllTiles();

    void reset();

private:
    std::unique_ptr<tson::Map> m_map { nullptr };
    std::string m_layerName { "" };

    //    std::map<std::pair<unsigned int, unsigned int>, std::shared_ptr<TileNode>> m_tiles;
    std::vector<std::shared_ptr<TileNode>> m_tiles;
    void parseTiles(std::shared_ptr<jt::TextureManagerInterface> textureManager);
    void createNodeConnections();
};

} // namespace tilemap
} // namespace jt
#endif // GUARD_JAMTEMPLATE_NODELAYER_HPP
