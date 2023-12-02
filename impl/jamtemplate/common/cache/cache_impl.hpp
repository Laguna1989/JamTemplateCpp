#ifndef JAMTEMPLATE_CACHE_IMPL_HPP
#define JAMTEMPLATE_CACHE_IMPL_HPP

#include <cache/cache_interface.hpp>

namespace jt {
class CacheImpl : public jt::CacheInterface {
public:
    CacheImpl(std::unique_ptr<jt::TilemapCacheInterface> tilemapCache = nullptr,
        std::shared_ptr<jt::LogHistoryInterface> logHistory = nullptr);

    jt::TilemapCacheInterface& getTilemapCache() override;
    std::shared_ptr<jt::LogHistoryInterface> getLogHistory() override;

private:
    std::unique_ptr<jt::TilemapCacheInterface> m_tilemapCache { nullptr };
    std::shared_ptr<jt::LogHistoryInterface> m_logHistory { nullptr };
};

} // namespace jt
#endif // JAMTEMPLATE_CACHE_IMPL_HPP
