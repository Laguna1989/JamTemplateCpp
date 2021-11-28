#include "objectlayer.hpp"
#include "conversions.hpp"

namespace jt {
namespace tilemap {

ObjectLayer::ObjectLayer(std::string const& path, std::string const& layerName)
{
    m_layerName = layerName;
    // TODO replace by tilemapManager, similar to TextureManager
    tson::Tileson parser;

    m_map = parser.parse(path);
    if (m_map->getStatus() != tson::ParseStatus::OK) {
        std::cout << "tilemap json could not be parsed.\n";
        throw std::logic_error { "tilemap json could not be parsed." };
    }
    parseObjects();
}

void ObjectLayer::parseObjects()
{
    for (auto& layer : m_map->getLayers()) {
        if (layer.getName() != m_layerName) {
            continue;
        }

        for (auto& obj : layer.getObjects()) {
            InfoRect infoRect { Conversion::vec(obj.getPosition()), Conversion::vec(obj.getSize()),
                obj.getRotation(), obj.getType(), obj.getName() };
            m_objectGroups.push_back(infoRect);
        }
    }
}

} // namespace tilemap
} // namespace jt
