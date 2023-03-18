#include "cache_null.hpp"

jt::CacheNull::CacheNull() { m_cache = std::make_unique<jt::TilemapCacheNull>(); }

jt::TilemapCacheInterface& jt::CacheNull::getTilemapCache() { return *m_cache; }
std::shared_ptr<jt::LogHistoryInterface> jt::CacheNull::getLogHistory() { return m_history; }
