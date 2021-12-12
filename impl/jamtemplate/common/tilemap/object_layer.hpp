#ifndef GUARD_JAMTEMPLATE_OBJECTLAYER_HPP
#define GUARD_JAMTEMPLATE_OBJECTLAYER_HPP

#include "info_rect.hpp"
#include "tilemap_manager_interface.hpp"
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
    ObjectLayer(std::string const& path,
        std::shared_ptr<jt::TilemapManagerInterface> tilemapManager, std::string const& layerName);

    /// get Object Groups from map
    /// \return the object group
    std::vector<InfoRect> getObjects();

private:
    std::vector<InfoRect> m_objectGroups {};

    void parseObjects(std::unique_ptr<tson::Map>& map, std::string const& layerName);
};

} // namespace tilemap
} // namespace jt

#endif // GUARD_JAMTEMPLATE_OBJECTLAYER_HPP
