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
    /// Constructor
    /// \param nodeTiles node tiles, either create them yourself or use TilesonLoader
    NodeLayer(std::vector<std::shared_ptr<TileNode>> nodeTiles);

    using Sptr = std::shared_ptr<NodeLayer>;
    std::shared_ptr<TileNode> getTileAt(unsigned int x, unsigned int y);
    std::vector<std::shared_ptr<TileNode>> getAllTiles();

    void reset();

private:
    std::vector<std::shared_ptr<TileNode>> m_nodeTiles;
    void createNodeConnections();
};

} // namespace tilemap
} // namespace jt
#endif // GUARD_JAMTEMPLATE_NODELAYER_HPP
