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

ObjectLayer::ObjectLayer(std::string const& path,
    std::shared_ptr<jt::TilemapManagerInterface> tilemapManager, std::string const& layerName)
{
    if (tilemapManager == nullptr) {
        throw std::invalid_argument { "tilemap manager dependency cannot be null" };
    }

    auto& map = tilemapManager->getMap(path);
    parseObjects(map, layerName);
}

void ObjectLayer::parseObjects(std::unique_ptr<tson::Map>& map, std::string const& layerName)
{
    for (auto& layer : map->getLayers()) {
        if (layer.getName() != layerName) {
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

std::vector<InfoRect> ObjectLayer::getObjects() { return m_objectGroups; }

} // namespace tilemap
} // namespace jt
