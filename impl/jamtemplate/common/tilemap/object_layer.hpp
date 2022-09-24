#ifndef JAMTEMPLATE_OBJECTLAYER_HPP
#define JAMTEMPLATE_OBJECTLAYER_HPP

#include <tilemap/info_rect.hpp>
#include <map>
#include <memory>
#include <string>
#include <tileson.h>
#include <vector>

namespace jt {
namespace tilemap {

class ObjectLayer {
public:
    using Sptr = std::shared_ptr<ObjectLayer>;

    /// Constructor
    /// \param objects list of objects. Create them yourself or via TilesonLoader
    explicit ObjectLayer(std::vector<InfoRect> const& objects);

    /// get Object Groups from map
    /// \return the object group
    std::vector<InfoRect> getObjects();

private:
    std::vector<InfoRect> m_objects {};
};

} // namespace tilemap
} // namespace jt

#endif // JAMTEMPLATE_OBJECTLAYER_HPP
