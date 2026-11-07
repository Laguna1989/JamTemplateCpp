#pragma once

#include <tilemap/tilemap_cache_interface.hpp>

namespace jt {
class TilemapCache : public jt::TilemapCacheInterface {
public:
    std::shared_ptr<tson::Map> get(std::string const& fileName) const override;
    std::size_t getNumberOfMaps() const;

private:
    mutable std::map<std::string, std::shared_ptr<tson::Map>> m_maps;
};
} // namespace jt
