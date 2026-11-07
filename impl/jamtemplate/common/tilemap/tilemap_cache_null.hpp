#pragma once

#include <tilemap/tilemap_cache_interface.hpp>

namespace jt {

class TilemapCacheNull : public jt::TilemapCacheInterface {
public:
    TilemapCacheNull();
    std::shared_ptr<tson::Map> get(std::string const& fileName) const override;

private:
    std::shared_ptr<tson::Map> m_map;
};

} // namespace jt
