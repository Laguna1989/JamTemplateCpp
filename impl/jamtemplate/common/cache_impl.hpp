#ifndef JAMTEMPLATE_CACHE_IMPL_HPP
#define JAMTEMPLATE_CACHE_IMPL_HPP

#include <cache_interface.hpp>

namespace jt {
class CacheImpl : public jt::CacheInterface {
public:
    jt::TilemapCache& getTilemapCache() override;

private:
    jt::TilemapCache m_tilemapCache;
};

} // namespace jt
#endif // JAMTEMPLATE_CACHE_IMPL_HPP
