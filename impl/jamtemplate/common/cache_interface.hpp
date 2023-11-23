#ifndef JAMTEMPLATE_CACHE_INTERFACE_HPP
#define JAMTEMPLATE_CACHE_INTERFACE_HPP

#include <log/log_history_interface.hpp>
#include <tilemap/tilemap_cache_interface.hpp>

namespace jt {
class CacheInterface {
public:
    /// Get the tilemap cache
    /// \return the tilemap cache
    virtual jt::TilemapCacheInterface& getTilemapCache() = 0;

    /// Get the log history
    /// \return the log history
    virtual std::shared_ptr<jt::LogHistoryInterface> getLogHistory() = 0;

    /// Destructor
    virtual ~CacheInterface() = default;

    // no copy, no move. Avoid slicing.
    CacheInterface(CacheInterface const&) = delete;
    CacheInterface(CacheInterface&&) = delete;
    CacheInterface& operator=(CacheInterface const&) = delete;
    CacheInterface& operator=(CacheInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    CacheInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_CACHE_INTERFACE_HPP
