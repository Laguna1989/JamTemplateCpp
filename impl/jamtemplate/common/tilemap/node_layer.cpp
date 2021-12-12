#include "node_layer.hpp"
#include "drawable_helpers.hpp"
#include "pathfinder/node.hpp"
#include "shape.hpp"

namespace jt {
namespace tilemap {

NodeLayer::NodeLayer(std::string const& path,
    std::shared_ptr<jt::TilemapManagerInterface> tilemapManager, std::string const& layerName,
    std::shared_ptr<jt::TextureManagerInterface> textureManager)
{
    if (tilemapManager == nullptr) {
        throw std::invalid_argument { "tilemap manager dependency cannot be null" };
    }

    auto& map = tilemapManager->getMap(path);
    parseTiles(textureManager, map, layerName);

    createNodeConnections();
}

void NodeLayer::parseTiles(std::shared_ptr<jt::TextureManagerInterface> textureManager,
    std::unique_ptr<tson::Map>& map, std::string const& layerName)
{
    for (auto& layer : map->getLayers()) {
        // skip all non-tile layers
        if (layer.getType() != tson::LayerType::TileLayer) {
            continue;
        }
        if (layer.getName() != layerName) {
            continue;
        }
        for (auto& [pos, tile] : layer.getTileObjects()) {

            bool isBlocked = false;
            auto blockedProperty = tile.getTile()->getProp("blocked");
            if (blockedProperty) {
                isBlocked = blockedProperty->getValue<bool>();
            }

            auto posx = std::get<0>(pos);
            auto posy = std::get<1>(pos);

            auto const ts = map->getTilesets().at(0).getTileSize();
            auto color = jt::MakeColor::FromRGBA(1, 1, 1, 100);
            if (!isBlocked) {
                color = jt::MakeColor::FromRGBA(255, 255, 255, 100);
            }

            std::shared_ptr<jt::Shape> drawable = jt::dh::createShapeRect(
                jt::Vector2f { static_cast<float>(ts.x - 1), static_cast<float>(ts.y - 1) }, color,
                textureManager);
            jt::Vector2f const positionInPixel
                = jt::Vector2f { static_cast<float>(ts.x * posx), static_cast<float>(ts.y * posy) };
            drawable->setPosition(positionInPixel);

            auto node = std::make_shared<jt::pathfinder::Node>();
            node->setPosition(
                jt::Vector2u { static_cast<unsigned int>(posx), static_cast<unsigned int>(posy) });

            m_tiles.emplace_back(
                std::make_shared<jt::tilemap::TileNode>(drawable, node, isBlocked));
        }
    }
}
void NodeLayer::createNodeConnections()
{
    for (auto& t : m_tiles) {
        if (t->getBlocked()) {
            continue;
        }

        auto const currentPos = t->getNode()->getTilePosition();
        for (int i = -1; i != 2; ++i) {
            for (int j = -1; j != 2; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                auto oi = static_cast<int>(currentPos.x) + i;
                auto oj = static_cast<int>(currentPos.y) + j;
                auto ot = getTileAt(static_cast<unsigned int>(oi), static_cast<unsigned int>(oj));
                if (ot) {
                    if (ot->getBlocked()) {
                        continue;
                    }
                    t->getNode()->addNeighbour(ot->getNode());
                }
            }
        }
    }
}

std::shared_ptr<TileNode> NodeLayer::getTileAt(unsigned int x, unsigned int y)
{
    auto it = std::find_if(m_tiles.begin(), m_tiles.end(), [x, y](auto tile) {
        return tile->getNode()->getTilePosition().x == x
            && tile->getNode()->getTilePosition().y == y;
    });
    if (it == m_tiles.end()) {
        return nullptr;
    }
    return *it;
}

std::vector<std::shared_ptr<TileNode>> NodeLayer::getAllTiles()
{
    //    std::vector<std::shared_ptr<TileNode>> tiles;
    //    for (auto kvp : m_tiles) {
    //        tiles.push_back(kvp.second);
    //    }
    //    return tiles;
    return m_tiles;
}
void NodeLayer::reset()
{
    for (auto& t : m_tiles) {
        auto color = jt::MakeColor::FromRGBA(1, 1, 1, 100);
        if (!t->getBlocked()) {
            color = jt::MakeColor::FromRGBA(255, 255, 255, 100);
        }
        t->setColor(color);
        t->reset();
    }
}

} // namespace tilemap
} // namespace jt
