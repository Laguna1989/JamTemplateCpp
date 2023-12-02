#include "cache_impl.hpp"
#include <log/log_history.hpp>
#include <tilemap/tilemap_cache.hpp>

jt::CacheImpl::CacheImpl(std::unique_ptr<jt::TilemapCacheInterface> tilemapCache,
    std::shared_ptr<jt::LogHistoryInterface> logHistory)
    : m_tilemapCache { std::move(tilemapCache) }
    , m_logHistory { logHistory }
{
    if (m_tilemapCache == nullptr) {
        m_tilemapCache = std::make_unique<jt::TilemapCache>();
    }
    if (m_logHistory == nullptr) {
        m_logHistory = std::make_shared<jt::LogHistory>();
    }
}

jt::TilemapCacheInterface& jt::CacheImpl::getTilemapCache() { return *m_tilemapCache; }
std::shared_ptr<jt::LogHistoryInterface> jt::CacheImpl::getLogHistory() { return m_logHistory; }
