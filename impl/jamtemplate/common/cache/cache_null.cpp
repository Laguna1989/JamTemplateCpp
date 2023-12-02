#include "cache_null.hpp"

jt::CacheNull::CacheNull() { m_tilemapCache = std::make_unique<jt::TilemapCacheNull>(); }

jt::TilemapCacheInterface& jt::CacheNull::getTilemapCache() noexcept { return *m_tilemapCache; }

std::shared_ptr<jt::LogHistoryInterface> jt::CacheNull::getLogHistory() noexcept { return m_history; }
