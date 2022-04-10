#include "object_layer.hpp"

jt::tilemap::ObjectLayer::ObjectLayer(std::vector<jt::tilemap::InfoRect> const& objects)
    : m_objects { objects }
{
}

std::vector<jt::tilemap::InfoRect> jt::tilemap::ObjectLayer::getObjects() { return m_objects; }
