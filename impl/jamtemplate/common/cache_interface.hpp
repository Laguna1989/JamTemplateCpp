#ifndef JAMTEMPLATE_CACHE_INTERFACE_HPP
#define JAMTEMPLATE_CACHE_INTERFACE_HPP

#include <tilemap/tilemap_cache_interface.hpp>

namespace jt {
class CacheInterface {
public:
    virtual ~CacheInterface() = default;

    // TODO make this function return an interface, not a concrete class.

    /// Get the tilemap cache
    /// \return
    virtual jt::TilemapCacheInterface& getTilemapCache() = 0;

    // TODO expand to other cached items
};
} // namespace jt

#endif // JAMTEMPLATE_CACHE_INTERFACE_HPP
