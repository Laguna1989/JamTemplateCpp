#include "cache_null.hpp"
#include <stdexcept>

jt::TilemapCache& jt::CacheNull::getTilemapCache()
{
    throw std::logic_error { "cannot ask for tilemap cache on nullCache." };
}
