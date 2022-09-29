#ifndef JAMTEMPLATE_CACHE_IMPL_HPP
#define JAMTEMPLATE_CACHE_IMPL_HPP

#include <cache_interface.hpp>

namespace jt {
class CacheImpl : public jt::CacheInterface {
public:
    explicit CacheImpl(std::unique_ptr<jt::TilemapCacheInterface> tilemapCache = nullptr);
    jt::TilemapCacheInterface& getTilemapCache() override;

private:
    std::unique_ptr<jt::TilemapCacheInterface> m_tilemapCache { nullptr };
};

} // namespace jt
#endif // JAMTEMPLATE_CACHE_IMPL_HPP
