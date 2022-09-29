#ifndef JAMTEMPLATE_TILEMAP_CACHE_HPP
#define JAMTEMPLATE_TILEMAP_CACHE_HPP

#include <tilemap/tilemap_cache_interface.hpp>

namespace jt {
class TilemapCache : public jt::TilemapCacheInterface {
public:
    std::shared_ptr<tson::Map> getMap(std::string const& fileName) const override;

private:
    mutable std::map<std::string, std::shared_ptr<tson::Map>> m_maps;
};
} // namespace jt

#endif // JAMTEMPLATE_TILEMAP_CACHE_HPP
