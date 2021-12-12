#include "object_layer.hpp"
#include "conversions.hpp"

namespace jt {
namespace tilemap {

ObjectLayer::ObjectLayer(std::vector<InfoRect> const& objects)
    : m_objects { objects }
{
}

std::vector<InfoRect> ObjectLayer::getObjects() { return m_objects; }

} // namespace tilemap
} // namespace jt
