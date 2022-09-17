#ifndef JAMTEMPLATE_TILEMAP_CACHE_HPP
#define JAMTEMPLATE_TILEMAP_CACHE_HPP

#include <tileson.h>

namespace jt {
class TilemapCache {
public:
    std::unique_ptr<tson::Map>& getMap(std::string const& fileName) const;

private:
    mutable std::map<std::string, std::unique_ptr<tson::Map>> m_maps;
};
} // namespace jt

#endif // JAMTEMPLATE_TILEMAP_CACHE_HPP
