#ifndef GUARD_JAMTEMPLATE_TILEMAP_MANAGER_TILESON_IMPL_HPP
#define GUARD_JAMTEMPLATE_TILEMAP_MANAGER_TILESON_IMPL_HPP

#include "tileson.h"

namespace jt {
class TilemapManagerTilesonImpl {
public:
    std::unique_ptr<tson::Map>& getMap(std::string const& fileName);

private:
    std::map<std::string, std::unique_ptr<tson::Map>> m_maps;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILEMAP_MANAGER_TILESON_IMPL_HPP
