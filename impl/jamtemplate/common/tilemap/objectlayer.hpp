#ifndef GUARD_JAMTEMPLATE_OBJECTLAYER_HPP
#define GUARD_JAMTEMPLATE_OBJECTLAYER_HPP

#include "info_rect.hpp"
#include "tileson.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {
namespace tilemap {

class ObjectLayer {
public:
    using Sptr = std::shared_ptr<ObjectLayer>;

    /// Constructor
    /// \param path path to the tilemap file
    explicit ObjectLayer(std::string const& path, std::string const& layerName = "");

    /// Get map size in Tiles
    /// \return map size in tiles
    jt::Vector2u getMapSizeInTiles();

    /// get Object Groups from map
    /// \return the object group
    std::map<std::string, std::vector<InfoRect>> getObjectGroups() { return m_objectGroups; };

private:
    std::unique_ptr<tson::Map> m_map { nullptr };
    // Map from object layer name to vector of objects, all rectangular.
    std::map<std::string, std::vector<InfoRect>> m_objectGroups {};

    void parseObjects();
};

} // namespace tilemap
} // namespace jt

#endif // GUARD_JAMTEMPLATE_OBJECTLAYER_HPP
