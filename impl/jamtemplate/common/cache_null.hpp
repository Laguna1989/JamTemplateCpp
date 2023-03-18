#ifndef JAMTEMPLATE_CACHE_NULL_HPP
#define JAMTEMPLATE_CACHE_NULL_HPP

#include <cache_interface.hpp>
#include <log/log_history_null.hpp>
#include <tilemap/tilemap_cache_null.hpp>
#include <memory>

namespace jt {

class CacheNull : public jt::CacheInterface {
public:
    CacheNull();
    jt::TilemapCacheInterface& getTilemapCache() override;

    std::shared_ptr<jt::LogHistoryInterface> getLogHistory() override;

private:
    std::unique_ptr<jt::TilemapCacheNull> m_cache { nullptr };
    std::shared_ptr<jt::null_objects::LogHistoryNull> m_history;
};
} // namespace jt
#endif // JAMTEMPLATE_CACHE_NULL_HPP
