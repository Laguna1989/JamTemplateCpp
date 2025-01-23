#include "tileson_loader.hpp"
#include <conversions.hpp>
#include <drawable_helpers.hpp>
#include <pathfinder/node.hpp>

namespace {
jt::tilemap::InfoRectProperties parseProperties(tson::PropertyCollection& props)
{
    jt::tilemap::InfoRectProperties properties;
    for (auto pkvp : props.getProperties()) {
        std::string const name = pkvp.first;
        if (pkvp.second.getType() == tson::Type::Boolean) {
            properties.bools[name] = pkvp.second.getValue<bool>();
        } else if (pkvp.second.getType() == tson::Type::Float) {
            properties.floats[name] = pkvp.second.getValue<float>();
        } else if (pkvp.second.getType() == tson::Type::Int) {
            properties.ints[name] = pkvp.second.getValue<int>();
        } else if (pkvp.second.getType() == tson::Type::String) {
            properties.strings[name] = pkvp.second.getValue<std::string>();
        } else {
        }
    }
    return properties;
}

jt::tilemap::TileInfo parseSingleTile(tson::TileObject& tile)
{
    auto const pos = jt::Conversion::vec(tile.getPosition());
    auto const size = jt::Conversion::vec(tile.getTile()->getTileSize());
    auto const id = static_cast<int>(tile.getTile()->getId()) - 1;

    return jt::tilemap::TileInfo { pos, size, id };
}

std::vector<std::shared_ptr<jt::Sprite>> loadTileSetSprites(std::shared_ptr<tson::Map> map,
    jt::TextureManagerInterface& textureManager, std::string const& tilesetPathPrefix = "assets/")
{
    std::vector<std::shared_ptr<jt::Sprite>> tileSetSprites;
    std::size_t offset { 0 };
    for (auto i = 0u; i != map->getTilesets().size(); ++i) {
        auto const tileset = map->getTilesets().at(i);
        auto const columns = tileset.getColumns();
        auto const rows = tileset.getTileCount() / columns;
        auto const ts = tileset.getTileSize();
        auto const tilesetName = tilesetPathPrefix + tileset.getImagePath().string();

        tileSetSprites.resize(offset + static_cast<size_t>(rows) * static_cast<size_t>(columns));
        for (int rowIndex = 0; rowIndex != rows; ++rowIndex) {
            for (int columnIndex = 0; columnIndex != columns; ++columnIndex) {
                {
                    tileSetSprites.at(offset + columnIndex + rowIndex * columns)
                        = std::make_shared<jt::Sprite>(tilesetName,
                            jt::Recti { columnIndex * ts.x, rowIndex * ts.y, ts.x, ts.y },
                            textureManager);
                }
            }
        }
        offset = tileSetSprites.size();
    }
    return tileSetSprites;
}

std::vector<jt::tilemap::TileInfo> loadTiles(
    std::string const& layerName, std::shared_ptr<tson::Map> map)
{
    std::vector<jt::tilemap::TileInfo> tiles;

    bool foundLayer { false };

    for (auto& layer : map->getLayers()) {
        // skip all non-tile layers
        if (layer.getType() != tson::LayerType::TileLayer) {
            continue;
        }
        if (layer.getName() == layerName) {
            foundLayer = true;
            for (auto& [_, tile] : layer.getTileObjects()) {
                tiles.emplace_back(parseSingleTile(tile));
            }
        }
    }

    if (!foundLayer) {
        std::cerr << "Warning: no tileset layer found with name : " << layerName << std::endl;
    }

    return tiles;
}

} // namespace

jt::tilemap::TilesonLoader::TilesonLoader(
    jt::TilemapCacheInterface& cache, std::string const& fileName)
    : m_tilemapCache { cache }
    , m_fileName { fileName }
{
}

std::vector<jt::tilemap::InfoRect> jt::tilemap::TilesonLoader::loadObjectsFromLayer(
    std::string const& layerName)
{
    auto map = m_tilemapCache.get(m_fileName);

    std::vector<InfoRect> objects;

    for (auto& layer : map->getLayers()) {
        if (layer.getName() != layerName) {
            continue;
        }

        for (auto& obj : layer.getObjects()) {
            InfoRect infoRect { Conversion::vec(obj.getPosition()), Conversion::vec(obj.getSize()),
                obj.getRotation(), obj.getType(), obj.getName(),
                parseProperties(obj.getProperties()) };
            objects.push_back(infoRect);
        }
    }
    return objects;
}

std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>>
jt::tilemap::TilesonLoader::loadNodesFromLayer(std::string const& layerName)
{
    auto map = m_tilemapCache.get(m_fileName);

    std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> nodes;

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

            auto const posx = std::get<0>(pos);
            auto const posy = std::get<1>(pos);

            auto node = std::make_shared<jt::pathfinder::Node>();
            node->setPosition(
                jt::Vector2u { static_cast<unsigned int>(posx), static_cast<unsigned int>(posy) });

            node->setBlocked(isBlocked);
            nodes.push_back(node);
        }
    }
    return nodes;
}

std::vector<std::shared_ptr<jt::tilemap::TileNode>>
jt::tilemap::TilesonLoader::loadTileNodesFromLayer(std::string const& layerName,
    jt::TextureManagerInterface& textureManager, bool dismissBlockedTiles)
{
    auto map = m_tilemapCache.get(m_fileName);

    std::vector<std::shared_ptr<TileNode>> nodeTiles;

    auto const nodes = loadNodesFromLayer(layerName);

    for (auto const& node : nodes) {
        if (dismissBlockedTiles) {
            if (node->getBlocked()) {
                continue;
            }
        }
        auto const ts = map->getTilesets().at(0).getTileSize();
        auto color = jt::Color { 1, 1, 1, 100 };
        if (!node->getBlocked()) {
            color = jt::Color { 255, 255, 255, 100 };
        }
        std::shared_ptr<jt::Shape> drawable = jt::dh::createShapeRect(
            jt::Vector2f { static_cast<float>(ts.x - 1), static_cast<float>(ts.y - 1) }, color,
            textureManager);
        jt::Vector2f const positionInPixel
            = jt::Vector2f { static_cast<float>(ts.x * node->getTilePosition().x),
                  static_cast<float>(ts.y * node->getTilePosition().y) };
        drawable->setPosition(positionInPixel);
        nodeTiles.emplace_back(std::make_shared<jt::tilemap::TileNode>(drawable, node));
    }
    return nodeTiles;
}

std::tuple<std::vector<jt::tilemap::TileInfo>, std::vector<std::shared_ptr<jt::Sprite>>>
jt::tilemap::TilesonLoader::loadTilesFromLayer(std::string const& layerName,
    jt::TextureManagerInterface& textureManager, std::string const& tilesetPathPrefix)
{
    auto const map = m_tilemapCache.get(m_fileName);

    return std::tuple<std::vector<TileInfo>, std::vector<std::shared_ptr<jt::Sprite>>>(
        loadTiles(layerName, map), loadTileSetSprites(map, textureManager, tilesetPathPrefix));
}

jt::TilemapCollisions jt::tilemap::TilesonLoader::loadCollisionsFromLayer(
    std::string const& layerName)
{
    TilemapCollisions collisions;
    auto map = m_tilemapCache.get(m_fileName);
    for (auto& layer : map->getLayers()) {
        // skip all non-tile layers
        if (layer.getType() != tson::LayerType::TileLayer) {
            continue;
        }
        if (layer.getName() != layerName) {
            continue;
        }
        for (auto& [pos, tile] : layer.getTileObjects()) {
            auto blockedProperty = tile.getTile()->getProp("blocked");
            if (!blockedProperty) {
                continue;
            }
            if (!blockedProperty->getValue<bool>()) {
                continue;
            }

            auto posx = std::get<0>(pos);
            auto posy = std::get<1>(pos);

            auto const ts = map->getTilesets().at(0).getTileSize();
            collisions.add(
                jt::Rectf { static_cast<float>(posx * ts.x), static_cast<float>(posy * ts.y),
                    static_cast<float>(ts.x), static_cast<float>(ts.y) });
        }
    }

    return collisions;
}

jt::Vector2u jt::tilemap::TilesonLoader::getMapSizeInTiles() const
{
    auto map = m_tilemapCache.get(m_fileName);
    auto const size = map->getSize();
    return jt::Vector2u { static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y) };
}
