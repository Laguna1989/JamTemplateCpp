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
    /// \param objects list of objects. Create them yourself or via TilesonLoader
    ObjectLayer(std::vector<InfoRect> const& objects);

    /// get Object Groups from map
    /// \return the object group
    std::vector<InfoRect> getObjects();

private:
    std::vector<InfoRect> m_objects {};
};

} // namespace tilemap
} // namespace jt

#endif // GUARD_JAMTEMPLATE_OBJECTLAYER_HPP
