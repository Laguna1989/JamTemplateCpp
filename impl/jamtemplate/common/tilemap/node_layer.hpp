#ifndef JAMTEMPLATE_NODELAYER_HPP
#define JAMTEMPLATE_NODELAYER_HPP

#include <texture_manager_interface.hpp>
#include <tilemap/tile_node.hpp>
#include <memory>
#include <tileson.h>
#include <unordered_map>
#include <vector>

namespace jt {
namespace tilemap {

class NodeLayer {
public:
    /// Constructor
    /// \param nodeTiles node tiles, either create them yourself or use TilesonLoader
    NodeLayer(std::vector<std::shared_ptr<TileNode>> nodeTiles);
    using Sptr = std::shared_ptr<NodeLayer>;
    std::shared_ptr<TileNode> getTileAt(jt::Vector2u const& pos);

    std::vector<std::shared_ptr<TileNode>> getAllTiles();

    void reset();

private:
    std::vector<std::shared_ptr<TileNode>> m_nodeTiles;
    void createNodeConnections();

    struct Vec2UHasher {
        std::size_t operator()(const jt::Vector2u& k) const
        {
            using std::hash;
            using std::size_t;
            using std::string;

            return ((hash<unsigned int>()(k.x) ^ (hash<unsigned int>()(k.y) << 1)) >> 1);
        }
    };

    std::unordered_map<jt::Vector2u, std::shared_ptr<TileNode>, Vec2UHasher> m_lookupHelper;
};

} // namespace tilemap
} // namespace jt
#endif // JAMTEMPLATE_NODELAYER_HPP
