#include "objectlayer.hpp"
#include "conversions.hpp"

namespace jt {
namespace tilemap {

void ObjectLayer::parseObjects()
{
    for (auto& layer : m_map->getLayers()) {
        const std::string currentGroupName = layer.getName();
        for (auto& obj : layer.getObjects()) {
            InfoRect infoRect { Conversion::vec(obj.getPosition()), Conversion::vec(obj.getSize()),
                obj.getRotation(), obj.getType(), obj.getName() };
            m_objectGroups[currentGroupName].push_back(infoRect);
        }
    }
}
} // namespace tilemap
} // namespace jt
