#ifndef JAMTEMPLATE_CACHE_INTERFACE_HPP
#define JAMTEMPLATE_CACHE_INTERFACE_HPP

#include <log/log_history_interface.hpp>
#include <tilemap/tilemap_cache_interface.hpp>

namespace jt {
class CacheInterface {
public:
    virtual ~CacheInterface() = default;

    /// Get the tilemap cache
    /// \return the tilemap cache
    virtual jt::TilemapCacheInterface& getTilemapCache() = 0;

    /// Get the log history
    /// \return the log history
    virtual std::shared_ptr<jt::LogHistoryInterface> getLogHistory() = 0;

    // TODO expand to other cached items
};
} // namespace jt

#endif // JAMTEMPLATE_CACHE_INTERFACE_HPP
