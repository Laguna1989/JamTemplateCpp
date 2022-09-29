
#include "cache_impl.hpp"
#include <tilemap/tilemap_cache.hpp>

jt::CacheImpl::CacheImpl(std::unique_ptr<jt::TilemapCacheInterface> tilemapCache)
    : m_tilemapCache { std::move(tilemapCache) }
{
    if (m_tilemapCache == nullptr) {
        m_tilemapCache = std::make_unique<jt::TilemapCache>();
    }
}

jt::TilemapCacheInterface& jt::CacheImpl::getTilemapCache() { return *m_tilemapCache; }
