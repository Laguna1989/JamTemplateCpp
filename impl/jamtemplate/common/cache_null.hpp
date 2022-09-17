#ifndef JAMTEMPLATE_CACHE_NULL_HPP
#define JAMTEMPLATE_CACHE_NULL_HPP

#include <cache_interface.hpp>

namespace jt {
class CacheNull : public jt::CacheInterface {
public:
    TilemapCache& getTilemapCache() override;
};
} // namespace jt
#endif // JAMTEMPLATE_CACHE_NULL_HPP
