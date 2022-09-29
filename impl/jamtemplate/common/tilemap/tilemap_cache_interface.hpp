#ifndef JAMTEMPLATE_TILEMAP_CACHE_INTERFACE_HPP
#define JAMTEMPLATE_TILEMAP_CACHE_INTERFACE_HPP

#include <memory>
#include <string>
#include <tileson.h>

namespace jt {

class TilemapCacheInterface {
public:
    virtual ~TilemapCacheInterface() = default;
    virtual std::shared_ptr<tson::Map> getMap(std::string const& fileName) const = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_TILEMAP_CACHE_INTERFACE_HPP
