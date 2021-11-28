#include "object_layer.hpp"
#include "conversions.hpp"

namespace jt {
namespace tilemap {

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
                obj.getRotation(), obj.getType(), obj.getName(),
                parseProperties(obj.getProperties()) };
            m_objectGroups.push_back(infoRect);
        }
    }
}

} // namespace tilemap
} // namespace jt
