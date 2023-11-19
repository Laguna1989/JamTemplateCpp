#include "tilemap_cache_null.hpp"

namespace jt {

TilemapCacheNull::TilemapCacheNull() { m_map = std::make_shared<tson::Map>(); }

std::shared_ptr<tson::Map> TilemapCacheNull::get(std::string const& /*unused*/
) const
{
    return m_map;
}

} // namespace jt
