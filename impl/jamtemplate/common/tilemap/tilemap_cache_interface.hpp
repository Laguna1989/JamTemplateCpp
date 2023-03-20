#ifndef JAMTEMPLATE_TILEMAP_CACHE_INTERFACE_HPP
#define JAMTEMPLATE_TILEMAP_CACHE_INTERFACE_HPP

#include <memory>
#include <string>
#include <tileson.h>

namespace jt {

class TilemapCacheInterface {
public:
    /// get map for a filename. This function is expected to cache the respective tson data.
    /// \param fileName map file to be loaded
    /// \return the tson map
    virtual std::shared_ptr<tson::Map> getMap(std::string const& fileName) const = 0;

    /// Destructor
    virtual ~TilemapCacheInterface() = default;

    // no copy, no move. Avoid slicing.
    TilemapCacheInterface(const TilemapCacheInterface&) = delete;
    TilemapCacheInterface(TilemapCacheInterface&&) = delete;
    TilemapCacheInterface& operator=(const TilemapCacheInterface&) = delete;
    TilemapCacheInterface& operator=(TilemapCacheInterface&&) = delete;

protected:
    // default default constructor can only be called from derived classes
    TilemapCacheInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_TILEMAP_CACHE_INTERFACE_HPP
