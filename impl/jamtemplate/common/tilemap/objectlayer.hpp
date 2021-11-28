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
    ObjectLayer(std::string const& path, std::string const& layerName);

    /// get Object Groups from map
    /// \return the object group
    std::vector<InfoRect> getObjects() { return m_objectGroups; };

private:
    std::unique_ptr<tson::Map> m_map { nullptr };

    std::string m_layerName { "" };

    // Map from object layer name to vector of objects, all rectangular.
    std::vector<InfoRect> m_objectGroups {};

    void parseObjects();
};

} // namespace tilemap
} // namespace jt

#endif // GUARD_JAMTEMPLATE_OBJECTLAYER_HPP
