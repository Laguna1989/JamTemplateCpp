#include "tileson_loader.hpp"
#include "conversions.hpp"
#include "drawable_helpers.hpp"
#include "pathfinder/node.hpp"
#include "shape.hpp"

namespace jt {
namespace tilemap {

namespace {
InfoRectProperties parseProperties(tson::PropertyCollection& props)
{
    InfoRectProperties properties;
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
} // namespace

TilesonLoader::TilesonLoader(
    std::shared_ptr<TilemapManagerInterface> tilemapManager, std::string const& fileName)
{
    m_tilemapManager = tilemapManager;
    m_fileName = fileName;
}

std::vector<InfoRect> TilesonLoader::loadObjectsFromLayer(std::string const& layerName)
{
    auto& map = m_tilemapManager->getMap(m_fileName);

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

std::vector<std::shared_ptr<TileNode>> TilesonLoader::LoadNodesFromLayer(
    std::string const& layerName, std::shared_ptr<jt::TextureManagerInterface> textureManager)
{
    auto& map = m_tilemapManager->getMap(m_fileName);

    std::vector<std::shared_ptr<TileNode>> nodeTiles;

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

            nodeTiles.emplace_back(
                std::make_shared<jt::tilemap::TileNode>(drawable, node, isBlocked));
        }
    }
    return nodeTiles;
}

} // namespace tilemap
} // namespace jt
