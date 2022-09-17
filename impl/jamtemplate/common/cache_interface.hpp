#ifndef JAMTEMPLATE_CACHE_INTERFACE_HPP
#define JAMTEMPLATE_CACHE_INTERFACE_HPP

#include <tilemap/tilemap_cache.hpp>

namespace jt {
class CacheInterface {
public:
    virtual ~CacheInterface() = default;

    // TODO make this function return an interface, not a concrete class.

    /// Get the tilemap cache
    /// \return
    virtual jt::TilemapCache& getTilemapCache() = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_CACHE_INTERFACE_HPP
